// DiplomacyBot.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <dpp/dpp.h>

const dpp::snowflake MY_GUILD_ID = 1059375022046707792;

int main()
{
    std::ifstream botToken ("token.txt");

    std::string botTokenString;

    if (botToken.is_open())
    {
        botToken >> botTokenString;
    }

    /* Create bot cluster */
    dpp::cluster bot(botTokenString);

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Handle simple slash command example */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {  
        if (event.command.get_command_name() == "ping")
        {
            event.reply("Pong!");
        }
    });

    /* Handle embed command for the github repository */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        /* Check if the gitrepo command was called */
        if (event.command.get_command_name() == "gitrepo")
        {
            /* Create an embed */
            dpp::embed embed = dpp::embed()
                .set_color(dpp::colors::purple)
                .set_title("Git Hub Repository")
                .set_url("https://github.com/the-fat-moose/discord-diplomacy-bot/")
                .set_author("Moose", "https://github.com/the-fat-moose/", "https://i.imgur.com/RFauyY6.png/")
                .set_description("Here is my repository!")
                .set_thumbnail("https://i.imgur.com/dJc2Rju.png/")
                .set_timestamp(time(0));

            /* Create a message with the content as our new embed */
            dpp::message msg(event.command.channel_id, embed);

            /* Reply to the user with the message, containing our embed */
            event.reply(msg);
        }
    });

    /* Handle command to display an image of the map */
    bot.on_slashcommand([&bot](const dpp::slashcommand_t& event) {
        /* Check if the displaymap command was called */
        if (event.command.get_command_name() == "displaymap")
        {
            // do something smile :D
        }
    });

    /* Register slash commands here in on_ready */
    bot.on_ready([&bot](const dpp::ready_t& event) {
        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>())
        {
            bot.global_command_create(dpp::slashcommand("ping", "Ping pong!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("gitrepo", "Check out my repository!", bot.me.id));
            bot.global_command_create(dpp::slashcommand("displaymap", "Displays an up to date game map", bot.me.id));
        }
    });

    /* Start the bot */
    bot.start(dpp::st_wait);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
