

MakeApp.chm : *.htm MakeApp.hhp MakeApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" MakeApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist MakeApp.chm del /f MakeApp.chm


Release/MakeApp.chm : MakeApp.chm
  copy $(MAKEDIR)\MakeApp.chm  $(MAKEDIR)\..\Release\MakeApp.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist MakeApp.chm del /f MakeApp.chm
  cd $(MAKEDIR)


Debug/MakeApp.chm : MakeApp.chm
  copy $(MAKEDIR)\MakeApp.chm  $(MAKEDIR)\..\Debug\MakeApp.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist MakeApp.chm del /f MakeApp.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/MakeApp.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/MakeApp.chm


