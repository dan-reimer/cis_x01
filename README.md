# cis_x01
CIS X01 - Para-course to make a webserver

This is a mostly-online course for those students interested in a more advanced programming project to challenge themselves. It receives no college credit but will provide practical experience in collaborative programming, git, c++, and the HTTP protocol. The end goal is a fully-functioning, albeit feature-limited, web server.

As a brief summary, git will allow you to work seperately on the same code and then merge all the work of several people into a single finished product. It also keeps track of all changes made by each individual and can go back to any time during the project to see how things have changed.

Lastly, I know several of you have experience with some of these items already. This is written to someone new to all the concepts so I apologize if parts of it seem overly basic.

## Instructions

### First day
The goal here is simply to become comfortable with git and working on a shared codebase. At the end, you should have a local copy of the project with your changes in a new branch.

#### Step 1 - Download git
Go to (https://msysgit.github.io/) and donwload the latest version of git. Be sure to install it with the *Use Git and optional Unix tools from the Windows Command Prompt* option, as well as *Checkout as-is, commit as-is*. The first will include a number of POSIX (Linux-like) tools such as grep, awk, and sed. These will help in the future. 

#### Step 2 - Compiler and editor
You have a couple of options here. I'll assume you are currently using Windows as your operating system and suggest you download Visual Studio Express for Windows Desktop. This is a free IDE (Integrated Development Environment - has both the editor and compiler) from Microsoft and the project is currently in a Visual Studio format. It is possible to use g++ in Linux but that will require modification of the code as it's not written for Linux at the moment.

#### Step 3 - Clone the git repository
To make a local copy of the project, you will need to clone the repository to a folder on your computer. This is where we will begin to use the command line. The CLI (command line interface) is heavily used in all programming so becoming comfortable with it will be very important.

- Press **Win + R**, or go to **Start > Run**
- Type **cmd** and press enter
- Decide where you will save your repos. I recommend *c:\code*. To create that, type: **mkdir c:\code**
- Change directories, **cd c:\code**
- Now we need to clone the github repo into this folder. Type: **git clone https://github.com/dan-reimer/cis_x01.git**
- Wait for the download to finish and then change directories into that folder: **cd cis_x01**
- List the contents to ensure it copied correctly, **dir**

#### Step 4 - Create a new branch
Git keeps track of all changes in *branches*. Each branch consists of a series of *commits*, a small change to the project. To ensure we have the freedom to make any changes we want without destroying the work of others, we create our own branches to work in.

- In the command window, type: **git branch my-branch-name**. *my-branch-name* can be anything you like, include a name someone else has used. These branches only exist on your own computer until we *merge* or *push* them to the server. This means you can change, add to, and delete whatever you like without having to worry about the effects.

#### Step 5 - Open the project in Visual Studio
Open Visual Studio, find where you cloned the project files, and open it. You will have the following files in the Solution explorer:

- core.hpp
- socket.hpp
- core.cpp
- main.cpp
- socket.cpp

**core.hpp** and **core.cpp** are going to be used in the future for the webserver but can be safely ignored for now. **socket.hpp** and **socket.cpp** are a very simple class I've written to make working with sockets a bit easier. I do not expect anyone to understand or change that code for now but you are definitely welcome to play with it!

**main.cpp** will have a very simple program that will connect to the localhost and download a website called "bccmdev.localhost". This will not work on your computer!

#### Step 6 - Experimentation
The program as it currently is will not work for you. It points to a website that should not exist on your computer. Try modifying the code to download from a public website.

At the top there is a `#define` called `REQ`. Anywhere where `REQ` appears in the code, it will be replaced with *exactly* what `REQ` is defined as, including any typos or code mistakes. The `\n` in the string means to start a *new line*. This is the same as `endl` is using `cout`, but slightly easier to type. 

Inside `main()` there is a line of `Winsock winsock;` - This is required for the class I wrote to work with Windows correctly. Again, it's not important that you understand how that works at the moment.

I've been using the word `class` for a while. This is a way to group several variables and functions and then be able to treat them as a single object. The class is only a *definition*. It does not actually allocate any memory, just defines what that memory will look like when we do. We can make as many *instances* of a class as we want. Each time we define a variable using the class (eg: `Socket tcp;` on line 16), it allocates memory for a new *instance* of the class.

Lastly, I've used something called *exceptions*. That's what the `try` and `catch` commands are for. For now, just understand that when `Socket` has an error inside the `try` block, it will immediately go to the `catch` block. `e.what()` will return a string with the problem and possibly an error code in it.

#### Step 7 - Sharing
Do something different with your copy of the project! Maybe pull out the titles of websites? Find the last date it was modified? Save the page to a file? Try anything you like. Next time you're with someone else doing this project, try showing them what you've done and see what they've done. It might teach you something or even give you an idea of what you could add.

Good luck! I look forward to seeing what you come up with. And remember, Google is your friend!

## Second Day
We will be planning the funcionality of the web server, working out the code layout as well as the flow-charts for each process.
