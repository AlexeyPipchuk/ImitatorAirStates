% --- Создание графиков и привязка их к определенным чекбоксам для
% данных ПОИ
function poiCheckboxAssignin(POI)
poi.ch5 = plot(POI.t(:),POI.x(:),'+g','Visible','off','DisplayName', 'ПОИ x');
poi.ch6 = plot(POI.t(:),POI.y(:),'+r','Visible','off','DisplayName', 'ПОИ y');
poi.ch7 = plot(POI.t(:),POI.z(:),'+b','Visible','off','DisplayName', 'ПОИ z');

assignin('base','poiPlot',poi);