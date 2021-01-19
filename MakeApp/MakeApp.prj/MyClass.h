// $description$


#pragma once


class $itemname$ {

public:

  $itemname$() { }
 ~$itemname$() { }

  $itemname$($itemname$& src) {copy(src);}
  $itemname$& operator= ($itemname$& src) {copy(src); return *this;}

private:

  void copy($itemname$& src);
  };
