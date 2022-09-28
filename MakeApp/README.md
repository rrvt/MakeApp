# MakeApp
An application to build a new application from a template.  There are three steps:

  - Specify the type of application:

    * An MFC Doc/View application with one document and one view.
    * An MFC Dialog Box with a menu, toolbar with limited controls, a status bar and an empty client
      area.

  - Specify the path to a place (directory aka folder) where the new application directory will be placed.
    Note, the application, say AlphaBeta, will be composed of four subdirectories:

    * AlphaBeta     -- at ...\BaseDir\AlphaBeta\AlphaBeta
    * AlphaBeta.hlp -- at ...\BaseDir\AlphaBeta\AlphaBeta.hlp
    * AlphaBeta.prj -- at ...\BaseDir\AlphaBeta\AlphaBeta.prj
    * AlphaBeta.wix -- at ...\BaseDir\AlphaBeta\AlphaBeta.wix

    Each subdirectory contains part of the project:

    * AlphaBeta     -- Solution file (The Visual Studio file that describes all the parts)
    * AlphaBeta.hlp -- Help files (see description of HTML Help Workshop 4.74.8702.0 below)
    * AlphaBeta.prj -- Project files from which the application is built
    * AlphaBeta.wix -- Wix Installation File (Product.wxs) from which an msi installer file is created

  - One caveat concerning the placement of the Library directory and the new project:  The new project
    and the Library should both have the same parent directory.  If that is not the case then the
    properties of the new project will need to be changed to reflect the location of the Library project
    file (i.e. ...\Library\Library.prj\Library.vcxproj).

  - The second step is to specify four attributes:

    * The Project Type: Doc/View or Dialog Box
    * The Project Name
    * An Englishish Title (appears on the upper border of the window and other places)
    * A Description of the the first page to appear (e.g. "Main Page")

    The smokestack Icon brings up a dialog box to specify these items.  When OK is selected the project
    is built.

  - For some reason, the solution file does not seem to contain the dependency list used by vs2017
    (or I could not deduce where it is in the solution file).  So there is a message
    at the end of the project production to set the dependencies in Visual Studio.  The prject may compile
    fine as the order of the projects in the solution file is correct, but there is not guarantee that
    it will stay that way.

It turns out that windows does not necessarily display and/or print the Courier New font as 1/10 of inch
wide characters.  So MakeApp implements a technique to adjust the size of the Courier New Font.  The
command to do this is under the Tools menu.  Using a ruler and the command one can find a suitable
constant to use for scaling the fonts.

## SlickEdit Project File

Should one have Slickedit then there is a feature in MakeApp to correct the slickedit project file to
correspond to the new project name.  This feature also will reorder the build menu and setup the builds
to clear the build output window before proceeding with the build. This command may be used on any
SlickEdit project file (i.e. an xxx.vpj file).

# AppT3mplate -- A Doc/View Application Template

A Template for a new App including features from the Library.  The MakeApp Help file describes the
organization of the application and describes how data is read and written from/to a file, and how
data may be stored and sent to the window (displayed) and how it may be printed (or print previewed).

There are commands in the application as examples of what might be done.  Here is a list of features
included in no particular order:

  - Determines the application ID to use for Explicitly seting Application User Model ID for the
    application.  Performs this task in the application's constructor.
  - IniFile management (see IniFile.h) -- Allows reading and writing varioous types to an old style
    name.ini file only needing the Section, Name and Value.
  - NotePad - A method of displaying information in the main window (MFC SDI only) using the "<<"
    operator.  Many types may be output without translation.  See the help file for more details about
    output to the display and printer.
  - Slightly expanded About Box which reads the information from the resources (xxx.rc strings, etc.)
  - Provide methods (function) in theApp for setting the windows Title Bar in two parts:
    <left part> - <right part>.
  - Support for setting the printer orientation (Portrait, Landscape) at the start of the program and
    changing the orientation in the Options Dialog Box.
  - Support for setting the display and printer scale factor in the Options Dialog that allows the
    Courier New font to be displayed at its defined size.
  - An Options dialog that changes the margins and orientation of the printed output.
  - A command to load a text file into a Store object using the CDoc file open and serialize features.
  - Examples of displaying and printing data in a Store object and in the global NotePad object.
  - Use the Extended Application class and MainFrame classes (i.e. CWinAppEx, CFrameWndEx).  The effect
    of using these two classes is to:
      - Allows the use of the 8 bit color table in the toolbar (i.e. 256 colors)
      - Provide Move and size management -- programs "remembers" where it was on the screen and how
        big it was.  It does use the registry and the appID computed in the constructor is used for
        the registry.
  - doc() -- returns pointer to document object
  - invalidate() -- cause the screen to be repainted, it doesn't happen automatically!
  - Help File has been added to TestApp with a simple one page help file.  The help file is constructed
    with HTML Help Workshop 4.74...  It may be found on Microsoft's web site by Google Searching for
    HTML Help Sorkshop.  Since HTML files are difficult to construct in the Workshop I use Dreamweaver
    to manage the files after some construction of the pages.

# DialogApp -- A Dialog Box Application

## Getting Started

The application, MakeApp, creates a new Application.  So copy the library source to a
directory like x:\Source\.  Then use the executable, MakeApp.exe, to specify the Source directory,
x:\source.  The folder icon or the File Menu is used to specify the source folder.

The second icon on the toolbar (which is supposed to look like a smokestack factory) creates the new
application.  Selecting the factory icon invokes a dialog box to accept the Project's Name, Window
(Visible) Name, and a Description (which also appears in the Window top border).

Once the application is created it can be compiled.  Note the Dependencies may need to be set in Visual
Studio sometime but it seems to compile correctly at the time of writing.

## History

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

### Where I Started

I found that creating a new application with Visual Studio and then trying to customize it like MakeApp
is annoyingly difficult.  So I tried another approach today. I just copied the entire MakeApp directory
to a new directory.  Then I changed all the file names to the one that I wanted for the new project, even
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

## Updates

### Update 9/28/22

Fixed the generation of UUIDs in the various files.  Other copy operations were included and fixed.

### Update 8/26/22

Add a copy of three additional directories from the application templates:  "<help dir>\Images" and
"AppT3mplate.hlp\Templates\".  Fixed the target name and root path in the "wxd" file (used by WixApp to
create a WIX Product File).

### Update 8/3/22

Minor Library updates .

### Update 4/15/22

Big adventure in February when I started moving to a new Win11 and Visual Studio 2022.  I now
feel that this version is working in the new environment.  There were several changes made to the app
in order to compile properly on VS22.

### Update 01/31/22

Updates to the library, mostly about the toolbar, but also NewAllocator, and a minor addition to
Expandable.

Also scrubbed the project files to remove all references to precompiled header files which I turned off
in VS17.  Unfortnately VS does not remove all references and pch files kept cropping up.  Not only does
that slow down the compiler but the files are large...

### Update 12/18/21

While creating a template for a dialog box only application with a toolbar the Library was added to and
changed to hopefully simplify toolbar creation.  This version of the toolbar includes buttons, edit boxes,
combo boxes and drop down menus as well as the traditional 16x15 icons.

MakeApp is a tradional App, has a traditional 16x15 pixel icon toolbar.  The AppTemplate is a
tradional application but it does have an example of all the toolbar button types.


### Update 11/13/21

But the major changes are in the library:

  - Expandable and ExpandableP -- moved the functions out of the class to make the compilation smaller,
also fixed one bug (or feature) in the ExpandableP insert sorted function that would throw out entries
that were already in in the array.
  - FileIO -- Changed the type of path from "String&" to "TCchar*".  It turns out that automatic
conversion from String to TCchar* is easy, but the reverse is is not easy.  Also added a function to
get the length of a file given a path.
  - FineName -- Added a function to get the directory name of from a path
  - NewAllocator -- Corrected the debug dependency from if to ifdef
  - ToolBar -- Added data for drop down menus

### Update 11/5/21

Release is different than Debug in the Build sense.  I played with the Visual Studio 2017 Properties
and here are the results.  The Release version doesn't need symbols or debug information so:

  - Highlight the executable project
  - Right Mouse and Select Properties
  - Choose C++/General page
  - For the line item "Debug Ifnormation Format" choose "None"
  - Then choose the Linker/Debugging page
  - For the line item "Generate Debug Info" choose "No"

I also looked at the various "Optimization" options to figure out which options make the most sense.
There did not seem to an obvious choice.  For these applications the choices were smaller or faster.  The
other features were not really important for MMI applications.  It was easy to measure size, speed not
so much.  Here are the results:

  - Choose C++/Optimication page in the executable project Properties
  - There are seven line items on this page.  The first few tests was with the "Optimization" line
where all the other items were either No, Neither or Disabled.
  - There are 4 labelled case and the results:
    * Option -- None      498 KB
    * Max Option -- Size  449 KB
    * Max Option -- speed 488 KB
    * Option speed        502 KB
  - There is also a Custom option and the sizes produced by the 6 other line items were between
491 KB and 514 KB in size
  - The line items also affect the Optimization choice (the first line item)
  - So I chose Max Option -- speed and the "Whole Program Optimization" -- "Yes" which yielded 458 KB
  - I also chose the Inline Function Expanson -- the "Only inline (/Ob1)" option
  - Also the Whole Program Optimization -- Yes (/GL)

Note:  I tried the Whole Program Optimization option on the static Library and it blew up to several
hundred MegaBytes.  However, when the following are chosen the size went down to 426 KB and supposedly
it was Max Speed:
  - Max Option Spped ()/O2)
  - Only Inline (/Ob1)
  - Whole Program Optimization (/GL)
  - Link Time Code Generation -- "Use Link Time Code Generation (/LTCG)"
  - References & COMDAT

Do the same for the Library except for Whole Program Optimization & of course no Linker optimization

Linker Properties

  - Choose the "Optimization" page in the Linker Properties
  - Set References to Yes (VS17 chose this)
  - Set Enable COMDAT Folding to yes (VS17 chose this)
  - Set Link Time Code Generation to  -- "Use Link Time Code Generation (/LTCG)"

These choices seem to work.

### Update 10/31/21

Changed Resources (i.e. xxx.rc data) access so that it will work with a dll.  Changed the logic in the
About Box code.  Some other library changes.  Some corresponding changes in the application.

### Update 4/17/21

Mostly Library updates but added logic to both MakeApp and TemplateApp to allow both the Options dialog
and the Printer Setup to view and modify the Printer Orientation (i.e. Portrait/Landscape).

### Update 3/8/21

Renamed PathDsc and changed the way it is initialized.

### Update 2/15/21

Fixed Backup date preparation to use 2 digit year instead of century.  Worked last year due to
coincidence (ugh!!!).

### Update 2/7/21

Updated Library for CodeGen and RWracesDB, updated icons on toolbar.

### Update 1/24/21

Toolbar icons had a background color that was not the same as the toolbar.  Firgured out how
to fix that.  Then since I had to start over with the icon pictures I chose new icons to
represent the actions.  Modified the help file accordingly.

Also created an Icon directory in this project to hold the original file containing the icon.
It may be a jpg, png or other image file.  Then the file is worked over to get a jpg file in
the 16 x 15 relative dimension format and the background changed to match the window toolbar.
This file is then saved.  Any toolbar may use the modified image in their toolbar by changing the size
to 16 x 15 pixels, copied and pasted onto the toolbar bmp file.  There is also a ColorTable in the Icon
file that includes the background color (index 255).  The ColorTable should be loaded into photoshop
toolbar page before modifying the toolbar.

## Update 1/19/21

Updated the MakeApp section of the readme.  MakeApp is now more or less complete.  It produces a new
application that compiles.  The MakeApp Help file includes a (hopefully) complete description of the
MakeApp commands and the organization of the Application Template which becomes the new application (with
all the names changed).

### Update 1/1821

The help for MakeApp has been extended to include a description of most of the
commands in MakeApp.  I've also included some description of the application
template, its components and how Serialize, Display and Print works in the
application.

### Update 11/7/20

Consolidating the changes uploaded yesterday.  Created a virtual module for the open notepad display and
printing.  The open notepad has the same problems as other reports with respect to interference between
the display and printing.  So the NoteRpt module allows separation of printing and displaying.

NoteRpt is stored in the library and provides a minimal package for dealing with open notepad output.
However, most of it is virtual and can be overridden to affect your version of the open notepad output.

### Update 11/6/20

Added provisions for loading, storing, displaying and printing various different data types.  This
required significant additions to the library.   One of the problems tackled with these changes revolves
around the fact that printing and displaying the same data is performed by two different threads.  Thus
the original simpleminded approach on having one data structure holding the data to be printed and
displayed failed to perform correctly as the threads interfered with each other.  The solution chosen
here is to provide a separate data structure holding the data to be printed and displayed.

Furthermove explored buttons, combo boxes and edit boxes being added to the ToolBar.  While these examples
perform no useful services they do perform.

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### August 12, 2020

Added a printer orientation feature so that the program may control the orientation (if it cares).  Some
modification will be required to disable this feature should the user prefer to let Windows make those
decisions in the printer setup.

### July 24, 2020

Consolidated the naming of the TextApp components so that when the new App is created the major components
are
 - MyAppII -- Solution file
 - MyAppII.hlp -- Help Project where the help files and htm are stored
 - MyAppII.prj == Project File and where the header and body files are stored

Made some changes in the way loops are formulated using
  OBIter iter(obj);                      // Where OBIter is the name of a class that implements the iter
  ...
  for (p = iter(); p; p = iter++) { ... }

instead of

  for (p = obj.startLoop(); p; p = obj.nextItem()) { ... }

For non-template classes the OBIter class is formed from a simple template typedef.

### Earlier

I added a help file template to the TestApp so that there is a start on a help document.  I spent a fair
amount of time trying to setup the Project Dependencies but the best that I could do is get the project
list in the order that they should be compiled in the solution file.  However, when one checks the
depedencies Visual Studio there is not specific dependecies specified.

## Prerequisites

Windows 7 or above.  visual Studio 2017 or above.

## Installing

This is a template.  Execute it, run the test.  Print the window, input/output
from the window.  That is all it does.

Now create your own app above and modify it to match this template.

## Authors

Robert R. Van Tuyl

Contact:  romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


