import asyncio
import websockets
import random
import time


async def send_data():


    async with websockets.connect('ws://** Your EC2 Instance IP **:8080') as websocket:
        while True:


            dummy_data = random.randint(0, 100)


            await websocket.send(str(dummy_data))


            print(f"Sent: {dummy_data}")


            await asyncio.sleep(1)
if __name__ == '__main__':
    asyncio.get_event_loop().run_until_complete(send_data())