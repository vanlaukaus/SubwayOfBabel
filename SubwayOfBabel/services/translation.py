import httpx
import logging
from typing import Optional

logging.basicConfig(level=logging.INFO)

async def translate(text: str, target_lang: str) -> Optional[str]:
    prompt = f"Translate this to {target_lang}: {text}"
    
    try:
        async with httpx.AsyncClient(timeout=30.0) as client:
            response = await client.post(
                "http://172.18.198.252:11434/api/generate",
                json={
                    "model": "mistral",
                    "prompt": prompt,
                    "stream": False,
                    "options": {"temperature": 0.3}
                }
            )
            
            # Check HTTP status first
            response.raise_for_status()
            
            # Validate JSON structure
            response_data = response.json()
            if "response" not in response_data:
                logging.error(f"Missing 'response' key in: {response_data}")
                return None
                
            return response_data["response"].strip()
            
    except httpx.HTTPStatusError as e:
        logging.error(f"HTTP error {e.response.status_code}: {e.response.text}")
    except httpx.RequestError as e:
        logging.error(f"Request failed: {str(e)}")
    except KeyError as e:
        logging.error(f"Missing expected key in response: {str(e)}")
    except Exception as e:
        logging.error(f"Unexpected error: {str(e)}")
        
    return None