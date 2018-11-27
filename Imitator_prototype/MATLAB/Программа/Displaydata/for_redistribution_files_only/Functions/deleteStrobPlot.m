% --- Удаление данных стробов
function deleteStrobPlot()
strob = evalin('base','strobPlot');
delete (strob.ch13);
delete (strob.ch14);
delete (strob.ch15);
