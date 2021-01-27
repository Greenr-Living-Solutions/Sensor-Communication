import websockets
import asyncio
from io import StringIO
import pandas as pd

print("Starting Server...")


async def readSensor(websocket, path):
    dataframe = pd.DataFrame()
    while 1:
        try:
            data = await websocket.recv()
            data = [data.split(" ")]
            print(data)
            dataframe = dataframe.append(data)
            dataframe.to_csv("data.csv", mode='w', header=False, index=False)
        except:
            websockets.serve("0.0.0.0", 8080,
                             ping_interval=None, ping_timeout=None)


start_server = websockets.serve(
    readSensor, "0.0.0.0", 8080, ping_interval=None, ping_timeout=None)

asyncio.get_event_loop().run_until_complete(start_server)
if asyncio.get_event_loop().is_closed():
    asyncio.get_event_loop().run_until_complete(start_server)
asyncio.get_event_loop().run_forever()
