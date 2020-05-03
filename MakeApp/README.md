# MakeApp
An application to customize TestApp (see below) to a new name.  There are two steps:

  - Specify the path to a place (directory aka folder) where the new application directory will be placed.
    Note, an application is composed of a solution file and one or more project files.  The solution file
    will be placed in a directory with the same name as the Project Name. For example a new spp named
    AlphaBeta, the solution directory will be in "...\AlphaBeta\AlphaBeta\" and the file name will be
    "AlphaBeta.sln".  The project file will be "...\AlphaBeta\AlphaBeta.prj\" and the project file name
    will be "AlphaBeta.vcxproj:.
  - One caveat concerning the placement of the Library directory and the new project:  The new project
    and the Library should both have the same parent directory.  If that is not the case then the
    properties of the new project will need to be changed to reflect the location of the Library project
    file (i.e. LibUni7.vcxproj).
  - Specify the Project Name (i.e. the directory name for the project and all critical directories and
    filenames within the outer directory).  Specify a Visible name that will be used in the left hand
    part of the window's title bar and the Window Description (the right hand part of the window title.)
  - One caveat.  For some reason, the solution file does not seem to contain the dependency
    list used by vs2017 (or I could not deduce where it is in the solution file).  So there is a message
    at the end of the project production to set the dependencies in Visual Studio.  The prject may compile
    fine as the order of the projects in the solution file is correct, but there is not guarantee that
    it will stay that way.

MakeApp then copies and changes all the relevant files to correspond to the instructions.

## SlickEdit Project File
Should one have Slickedit then there is a feature in MakeApp to correct the slickedit project file to
correspond to the new project name.

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

Since building MakeApp I have been able to create a new App with a couple of clicks and filling some
of the relevant information (see above).  The history section below suggests what is necessary to create
a new App which with MakeApp is unneccessary.  The setup is in the project file which is just modified
to reflect the new application name.  After making the app visual studio can be told to build it and
the new app should behave as test app behaves.  Then the fun begins...

I've also constructed an App to sort the file names in a project based only on the file name and not the
path.  Makes it a bit easier to find things.  It is called AdjProj.

### History
I found that creating a new application with Visual Studio and then trying to customize it like MakeApp
is quite difficult.  So I tried another approach today. I just copied the entire MakeApp directory to a
new directory.  Then I changed all the file names to the one that I wanted for the new project, even
the solution and project file names.
```
   All MakeAppxxx.xxx were changed to MyAppxxx.xxx -- took 10 minutes or so as there are fewer than 15
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


