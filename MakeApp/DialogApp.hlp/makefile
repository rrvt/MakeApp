

DialogApp.chm : *.htm DialogApp.hhp DialogApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" DialogApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F DialogApp.chm


Release/DialogApp.chm : DialogApp.chm
  copy $(MAKEDIR)\DialogApp.chm  $(MAKEDIR)\..\Release\DialogApp.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del DialogApp.chm
  cd $(MAKEDIR)


Debug/DialogApp.chm : DialogApp.chm
  copy $(MAKEDIR)\DialogApp.chm  $(MAKEDIR)\..\Debug\DialogApp.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del DialogApp.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/DialogApp.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/DialogApp.chm


