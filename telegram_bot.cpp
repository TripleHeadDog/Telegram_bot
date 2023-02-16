#include <stdio.h>
#include <tgbot/tgbot.h>
#include <vector>
#include <ctime>

using namespace std;
using namespace TgBot;

vector <string> Bot_commands = {"start","time","love"};
string get_time_as_str(){
time_t now = time(NULL);
tm* ptr = localtime(&now);
char buf[32];
strftime(buf, 32, "%c",ptr);
return buf;
}


int main() {
setlocale(LC_ALL, "ru");
    TgBot::Bot bot("6053179342:AAHUi0uwb9nQLNH0S1Rte1HWa4LeIklTKUc");

    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);
    vector<InlineKeyboardButton::Ptr> buttons;
    InlineKeyboardButton::Ptr checkButton (new InlineKeyboardButton);
    checkButton->text = "Лави LOVE";
    checkButton->callbackData = "check";
    buttons.push_back(checkButton);
    keyboard->inlineKeyboard.push_back(buttons);

    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Привет, Арина!");


    });

    bot.getEvents().onCommand("time", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Rechitsa:\n"+get_time_as_str());


    });

    bot.getEvents().onCommand("love", [&bot, &keyboard](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, " Что именно?", false, 0, keyboard);
        


    });
    

    bot.getEvents().onCallbackQuery([&bot , &keyboard](CallbackQuery::Ptr query){

        if(StringTools::startsWith(query->data,"check")){

             bot.getApi().sendPhoto(query->message->chat->id, InputFile::fromFile("pizda.jpg","image/jpg"));
            bot.getApi().sendMessage(query->message->chat->id, "айм то вери вери ю лави лави");
           
             

        }
        else{

        }
    });
    


    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        for (const auto& command : Bot_commands)
        {
        if('/'+command==message->text){
        return ;
        }
        }
        bot.getApi().sendPhoto(message->chat->id, InputFile::fromFile("pepe.jpg","image/jpg"));
        bot.getApi().sendMessage(message->chat->id,"Я нихуя не понял -_-");

    });
    try {
        printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
      
            printf("Long poll started\n");

            longPoll.start();
        }
    } catch (TgBot::TgException& e) {
        printf("error: %s\n", e.what());
    }
    return 0;
}
