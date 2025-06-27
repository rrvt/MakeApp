

Dialog4pp.chm : *.htm Dialog4pp.hhp Dialog4pp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" Dialog4pp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist Dialog4pp.chm del /f Dialog4pp.chm


Release/Dialog4pp.chm : Dialog4pp.chm
  copy $(MAKEDIR)\Dialog4pp.chm  $(MAKEDIR)\..\Release\Dialog4pp.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  if exist Dialog4pp.chm del /f Dialog4pp.chm
  cd $(MAKEDIR)


Debug/Dialog4pp.chm : Dialog4pp.chm
  copy $(MAKEDIR)\Dialog4pp.chm  $(MAKEDIR)\..\Debug\Dialog4pp.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  if exist Dialog4pp.chm del /f Dialog4pp.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/Dialog4pp.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/Dialog4pp.chm


