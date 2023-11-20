import asyncio
import websockets
async def receive_data(websocket, path):
    async for message in websocket:
        print(f"Received: {message}")
if __name__ == '__main__':
    start_server = websockets.serve(receive_data, '0.0.0.0', 8080)
    asyncio.get_event_loop().run_until_complete(start_server)
    asyncio.get_event_loop().run_forever()
