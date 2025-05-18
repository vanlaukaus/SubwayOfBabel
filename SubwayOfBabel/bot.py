import os
import re
import json
import httpx
import asyncio
import logging
from pathlib import Path
from telegram import Update
from telegram.ext import Application, MessageHandler, filters
from dotenv import load_dotenv

load_dotenv()
logging.basicConfig(
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s",
    level=logging.INFO
)
logger = logging.getLogger(__name__)

flag_map = {
    "en": "🇬🇧",
    "de": "🇩🇪",
    "fr": "🇫🇷",
    "ja": "🇯🇵",
    "zh": "🇨🇳",
    "tr": "🇹🇷",
    "kk": "🇰🇿",
    "hi": "🇮🇳",
    "vi": "🇻🇳"
}


async def config_poller():
    while True:
        await config.refresh_languages()
        await asyncio.sleep(5)
        
class LanguageConfig:
    def __init__(self):
        self.config_path = Path("C:/SubwayOfBabel/config/languages.json")
        self.config_path.parent.mkdir(parents=True, exist_ok=True)
        self.active_langs = ["ru"]
        self.last_modified = 0
        self.lock = asyncio.Lock()
    
        
    async def refresh_languages(self):
        async with self.lock:
            try:
                if not self.config_path.exists():
                    return
                
                stat = self.config_path.stat()
                if stat.st_mtime > self.last_modified:
                    self.last_modified = stat.st_mtime
                    with open(self.config_path, 'r', encoding='utf-8') as f:
                        langs = json.load(f)
                        self.active_langs = ["ru"] + [
                            lang.strip().lower() 
                            for lang in langs 
                            if lang.strip().lower() != "ru" and len(lang.strip()) == 2
                        ]
                        logger.info(f"Active languages updated to: {self.active_langs}")
            except Exception as e:
                logger.warning(f"Config load error: {str(e)}")

config = LanguageConfig()

async def translate(text: str, target_lang: str) -> str:
    try:
        prompt = (
            f"<s>[INST] "
            f"<translate_task>"
            f"<rules>"
            f"1. EXACT translation to {target_lang.upper()}\n"
            f"2. PRESERVE numbers/dates/formatting\n"
            f"3. NO explanations/additions\n"
            f"4. OUTPUT ONLY translation\n"
            f"</rules>"
            f"<source_text>{text}</source_text>"
            f"</translate_task> "
            f"[/INST]"
            f"<translation>"
        )
        
        async with httpx.AsyncClient(timeout=30) as client:
            response = await client.post(
                "http://localhost:11434/api/generate",
                json={
                    "model": "mistral",
                    "prompt": prompt,
                    "stream": False,
                    "options": {
                        "temperature": 0.01, 
                        "stop": ["</translation>", "\n"]
                    }
                }
            )
            response.raise_for_status()
            
            # Отделение переведённого текста
            raw = response.json().get("response", "")
            translated = raw.split("<translation>")[-1].split("</translation>")[0].strip()
            
            # Конечная очистка выходных данных
            translated = translated.split('Note:')[0].split('Warning:')[0].strip('"').strip()
            return translated if translated and translated != text else ""
            
    except Exception as e:
        logger.error(f"Translation error ({target_lang}): {str(e)}")
        return ""
        
def validate_translation(original: str, translated: str) -> bool:
    invalid_patterns = [
        r"\b(?:example|note:|warning:|http|www\.)\b",
    ]
    
    original_items = re.findall(r'\d+[/\-]\d+[/\-]\d*|\d+:\d+', original)
    translated_items = re.findall(r'\d+[/\-]\d+[/\-]\d+|\d+:\d+', translated)
    
    return (
        not any(re.search(p, translated, re.IGNORECASE) for p in invalid_patterns)
        and (original_items == translated_items)
    )

async def handle_message(update: Update, context):
    try:
        await config.refresh_languages()
        msg = update.channel_post
        if not msg:
            return

        # Extract original text first
        original_text = msg.caption or msg.text or ""
        translations = {"🇷🇺": original_text.strip()}
        
        try:
            await msg.delete()
        except Exception as e:
            logger.error(f"Delete failed: {str(e)}")

        active_langs = [lang for lang in config.active_langs if lang != "ru"]
        
        if original_text.strip():
            tasks = [translate(original_text, lang) for lang in active_langs]
            results = await asyncio.gather(*tasks)
            
            for lang, translated in zip(active_langs, results):
                if translated and validate_translation(original_text, translated):
                    translations[flag_map[lang]] = translated

        if msg.photo:
            photo = msg.photo[-1].file_id
            await context.bot.send_photo(
                chat_id=msg.chat.id,
                photo=photo,
                caption="\n".join(f"{flag} {text}" for flag, text in translations.items()) if translations else None
            )
        elif msg.document:
            await context.bot.send_document(
                chat_id=msg.chat.id,
                document=msg.document.file_id,
                caption="\n".join(f"{flag} {text}" for flag, text in translations.items()) if translations else None
            )
        elif msg.text or msg.caption:
            await context.bot.send_message(
                chat_id=msg.chat.id,
                text="\n".join(f"{flag} {text}" for flag, text in translations.items())
            )

    except Exception as e:
        logger.error(f"Handler error with text '{original_text[:50]}...': {str(e)}")

if __name__ == "__main__":
    application = Application.builder() \
        .token(os.getenv("TELEGRAM_TOKEN")) \
        .build()
    application.add_handler(MessageHandler(filters.ChatType.CHANNEL, handle_message))

    loop = asyncio.get_event_loop()
    loop.create_task(config_poller())

    try:
        logger.info("Starting bot...")
        application.run_polling()
    except KeyboardInterrupt:
        logger.info("Bot stopped")