import sys
import os
import asyncio

# Add project root to Python path
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '.')))

from services.translation import translate

async def test():
    result = await translate("Hello world", "German")
    print(f"Test translation: {result}")

if __name__ == "__main__":
    asyncio.run(test())