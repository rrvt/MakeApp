

MakeAppII.chm : *.htm MakeAppII.hhp MakeAppII.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" MakeAppII


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F MakeAppII.chm


Release/MakeAppII.chm : MakeAppII.chm
  copy $(MAKEDIR)\MakeAppII.chm  $(MAKEDIR)\..\Release\MakeAppII.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del MakeAppII.chm
  cd $(MAKEDIR)


Debug/MakeAppII.chm : MakeAppII.chm
  copy $(MAKEDIR)\MakeAppII.chm  $(MAKEDIR)\..\Debug\MakeAppII.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del MakeAppII.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/MakeAppII.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/MakeAppII.chm


