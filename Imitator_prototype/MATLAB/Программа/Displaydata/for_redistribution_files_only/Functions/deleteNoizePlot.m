% --- Удаление данных шумов
function deleteNoizePlot()
noize = evalin('base','noizePlot');
delete (noize.ch9);
delete (noize.ch10);
delete (noize.ch11);