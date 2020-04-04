# TestApp
A Template for a new App including features from the Library.  Here is a list of features included in
no particular order:
  - Determines the application ID to use for Explicitly seting Application User Model ID for the
    application.  Performs this task in the application's constructor.
  - IniFile management (see IniFile.h) -- Allows reading and writing varioous types to an old style
    name.ini file only needing the Section, Name and Value.
  - NotePad - A method of displaying information in the main window (MFC SDI only) using the "<<"
    operator.  Many types may be output without translation.
  - Slightly expanded About Box which reads the information from the resources (xxx.rc strings, etc.)
  - Provide methods (function) in theApp for setting the windows Title Bar in two parts:
    <left part> - <right part>.
  - Printer output from main screen content
  - File read/write to/from the main window from/to a text file.  One gets to choose the extension and
    other attributes to display in the file dialog box.  Added logic to Doc to specify the name, default
    extension, the pattern for the display of files in the file dialog box and the title on the file
    dialog box.
  - Use the Extended Application class and MainFrame classes (i.e. CWinAppEx, CFrameWndEx).  The effect
    of using these two classes is to:
      - Allows the use of the 8 bit color table in the toolbar (i.e. 256 colors)
      - Provide Move and size management -- programs "remembers" where it was on the screen and how
        big it was.  It does use the registry and the appID computed in the constructor is used for
        the registry.
  - doc() -- returns pointer to document object
  - invalidate() -- cause the screen to be repainted, it doesn't happen automatically!

## Getting Started

Create a new Application using the following parameters:
  - New MFC App
  - Single Document
  - Document/View Architecture
  - MFC Standard Style
  - Windows 7 visual style and colors
  - Disable (uncheck) visual style switching
  - Use Menu bar and toolbar
  - Uncheck User-defined toolbars and images
  - Uncheck Personalized menu behavior
  - Use a Browser Style Toolbar
  - Disable ActiveX controls
  - Disable Common Control Manfest
  - Disable Restart Manager
  - I usually remove the beginning C from the class names
  - For the View class chose the CScrolView as the Base class

I found that creating a new application with Visual Studio and then trying to customize it like TestApp
is quite difficult.  So I tried another approach today. I just copied the entire TestApp directory to a
new directory.  Then I changed all the file names to the one that I wanted for the new project, even
the solution and project file names.
```
   All TestAppxxx.xxx were changed to MyAppxxx.xxx -- took 10 minutes or so as there are fewer than 15
   such files.
```
I use SlickEdit for editing and it keeps its own solution and project files.  I deleted those files as
SlickEdit creates then from the Visual Studio solution and project files.

Then I used Visual Studio to delete the project it could not find
and load in the project (new name) into the solution.
Did the same maneuver with the renamed files.
Don't forget the res files (both renaming them and including them into the project again).  Then I did
some renaming in the files themselves to the new names.

The result is after a couple of false starts everything compiled and executed.

### Prerequisites

Windows 7 or above.  visual Studio 2017 or above.

### Installing

This is a template.  Execute it, run the test.  Print the window, input/output
from the window.  That is all it does.

Now create your own app above and modify it to match this template.

## Authors

Robert R. Van Tuyl

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


