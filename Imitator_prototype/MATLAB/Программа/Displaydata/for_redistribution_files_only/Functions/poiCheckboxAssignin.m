% --- �������� �������� � �������� �� � ������������ ��������� ���
% ������ ���
function poiCheckboxAssignin(POI)
poi.ch5 = plot(POI.t(:),POI.x(:),'+g','Visible','off','DisplayName', '��� x');
poi.ch6 = plot(POI.t(:),POI.y(:),'+r','Visible','off','DisplayName', '��� y');
poi.ch7 = plot(POI.t(:),POI.z(:),'+b','Visible','off','DisplayName', '��� z');

assignin('base','poiPlot',poi);