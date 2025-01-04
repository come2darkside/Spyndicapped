# Spyndicapped

Spy of your users with Microsoft UIA! Inspired by vx-underground [paper](https://samples.vx-underground.org/Papers/Windows/Windows%20COM/2022-10-28%20-%20Using%20Windows%20IUIAutomation%20for%20spyware%20and%20other%20malicious%20purposes.html).
![изображение](https://github.com/user-attachments/assets/052ae59a-67d8-4d04-9fa1-847a34562af6)

```shell
PS A:\ssd\gitrepo\Spyndicapped_dev\x64\Debug> .\Spyndicapped.exe -h

              ._
                |
                |
                |L___,
              .' '.  T
             :  *  :_|
              '._.'   L

[Spyndicapped]
CICADA8 Research Team
Christmas present from MzHmO

There are different work modes:
[FIND mode]
        Displays the windows available for spying with --window or --pid
        [EXAMPLES]
         Spyndicapped.exe find
[SPY mode]
        Window(s) spying mode
         --window <name> <- grabs information from that window
         --pid <pid> <- grabs information from that process (GUI Required)
         --logfile <filename> <- store all events into the log file
         --ignore-handlers <- I have created handlers for various apps, but u can use the generic HandleOther() with this flag
         --timeout <sec> <- interval to process events (default 1 sec)
         --no-uia-events <- disables MyAutomationEventHandler
         --no-property-events <- disables MyPropertyChangedEventHandler
        [EXAMPLES]
         Spyndicapped.exe spy
         Spyndicapped.exe spy --window "Program Manager"
         Spyndicapped.exe spy --pid 123
[Other]
         --debug <- displays more information
```

# TL;DR

```shell
# Spy the whole system (high load may be!)
  .\Spyndicapped spy

# And log everything into the file
  .\Spyndicapped spy --logfile 1.txt

# Find target and spy by the pid
  .\Spyndicapped find
  .\Spyndicapped spy --pid <pid from find command>
```

Keepass looting example:
![изображение](https://github.com/user-attachments/assets/e14839f0-5692-4eed-868e-4dd3e9336667)

![изображение](https://github.com/user-attachments/assets/c7e7c40c-5137-44c0-a96d-b044505a177c)


# How it works
So, there is a Windows User Automation framework that allows you to work with any Windows graphical elements. I just studied it over the New Year holidays and made a small POC :P It just so happens that in parallel I became an expert in Windows programming for handicapped people. Why didn't anyone tell me about this when I first started learning pentest?

In fact, I have two handlers:
- `MyAutomationEventHandler` — UIA basic event processing (Ex: opened a new window);
- `MyPropertyChangedEventHandler` — property changed event handling (Ex: inserted a value).

They handle all the GUI changes we are interested in: data input, text copying, data modification. Among other things, I've added handlers under different processes and even domains in the browser so you can get more familiar with the framework! See the examples below for more details. Also, I added an example of using patterns (one of the UIA components) on the example of KeePass looting.

With this project you will be able to learn Windows UIA! I use almost all concepts: event handling, pattern calling, tree traversal, item lookup.

You can find out more details in this article on medium.

# Usage examples

Check keepass looting above :))

In addition, the tool can parse Telegram messages:
![изображение](https://github.com/user-attachments/assets/03458550-9aef-4eaf-b99c-1c98e62ba61e)

Note that the tool captures the text you enter, shows the sender's name and the recipient's name. In this case, I'm writing a message to a chat.

The exact same functionality is supported for the Web version of Slack:

![изображение](https://github.com/user-attachments/assets/b5559d1f-8916-4b58-ac0d-016c62e2aae4)

And whatsapp web:
![изображение](https://github.com/user-attachments/assets/b88fb837-4cba-4312-8f25-6eb766239544)



