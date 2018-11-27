% --- Удаление графиков ПОИ
function deletePOIPlot()
poi = evalin('base','poiPlot');
delete (poi.ch5);
delete (poi.ch6);
delete (poi.ch7);