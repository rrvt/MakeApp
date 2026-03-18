

MakeApp.chm : *.htm MakeApp.hhp MakeApp.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" MakeApp


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  if exist MakeApp.chm del /f MakeApp.chm


$(TgtFolder)/MakeApp.chm : MakeApp.chm
  copy $(MAKEDIR)\MakeApp.chm  $(MAKEDIR)\..\$(TgtFolder)\MakeApp.chm


$(TgtFolder)/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\$(TgtFolder)
  if exist MakeApp.chm del /f MakeApp.chm
  cd $(MAKEDIR)


$(TgtFolder)/Rebuild.rbd : $(TgtFolder)/Clean.cln $(TgtFolder)/MakeApp.chm


