

TestApp.chm : *.htm TestApp.hhp TestApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" TestApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F TestApp.chm


Release/TestApp.chm : TestApp.chm
  copy $(MAKEDIR)\TestApp.chm  $(MAKEDIR)\..\Release\TestApp.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del TestApp.chm
  cd $(MAKEDIR)


Debug/TestApp.chm : TestApp.chm
  copy $(MAKEDIR)\TestApp.chm  $(MAKEDIR)\..\Debug\TestApp.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del TestApp.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/TestApp.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/TestApp.chm


