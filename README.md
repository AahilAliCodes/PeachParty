# PeachParty

## Notes for Visual C++ users:

- If the Windows skeleton doesn't build for you, you probably need to ensure that your project is using Windows SDK Version 10.0.19041.0 or 10.18362.0 or 10.0.17763.0 (or possibly 10.0.22000.0). To do this:
Launch the Visual Studio Installer, find your version of Visual Studio, and select Modify. In the list on the right side of optional packages, make sure SDK 10.0.19041.0 or 10.18362.0 or 10.0.17763.0 (or possibly 10.0.22000.0) is selected.
After modifying your Visual Studio installation, open the project in Visual Studio and right-click on Solution 'PeachParty' above the list of source files. Select Retarget Solution and choose the newly installed version of the SDK.
Build the project.
- Also, if the skeleton crashes after 1 to 30 seconds with a dialog box showing an error code 0xc0000022, try disabling your antivirus software and building the executable.

## Notes for Xcode users (MacOS):

- You might get a message at startup relating to the Assets directory. If you want to fix the issue just for this project, select File / Project Settings... and for Derived Data Location, select Project-relative Location. If instead you want to fix it for every project you create with Xcode, select Xcode / Preferences... and for the Derived Data, select Relative. Alternatively, you could simply change the assetDirectory string literal in main.cpp to be a full path name to wherever you choose to put the Assets directory.

- If you build and run your program from within Xcode, the Assets directory should be in
the directory yourProjectDir/DerivedData/yourProjectName/Build/Products/Debug (e.g.,
/Users/ethel/CS32Project3/DerivedData/PeachParty/Build/Products/Debug). On the
other hand, if you launch the program by double-clicking on the executable file, the
Assets directory should be in your home directory (e.g., /Users/ethel).
