import websockets.*;
  
Table table;

WebsocketServer ws;
int now;

void setup(){
  ws = new WebsocketServer(this,8080,"");
  
  table = new Table();
  
  table.addColumn("Time");
  table.addColumn("Sound");
}

void webSocketServerEvent(String msg){ 
  String s = msg;
  String[] list = split(s, ",");
  println(list[0]);
  TableRow newRow = table.addRow();
  newRow.setString("Time", list[0]);
  newRow.setString("Sound", list[1]);
 
  saveTable(table, "/Users/sachaverlon/Desktop/Greenr/DATA/sound-data2.csv");
 
}
