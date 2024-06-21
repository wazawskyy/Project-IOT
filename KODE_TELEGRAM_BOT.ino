void handleMewMesaaages(int numNewMeasaages)
{
  serial.printIn("handleNewMesaages");
  serial.printIn(String(numNewMessages));

  for (int i = 0; i < numNewMessage; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == ""){
      from_name = "Guest";
    }
    
    if (text == "/start"){
      String welcome = "Hi, "+ from_name + ".\n";
      welcome += "Sistem sudah online :) \n";

      bot.sendMessages(chat_id, welcome);
    }
    
    if (text.equals("/cek_suhu")) {//Corrected the clossing paremthesis
    String welcome = "Suhu saat ini : ";
    welcome += String(t);
    welcome += "°C";
    bot.sendmessage(chat_id, welcome);
    }
  }
}