% --- �������� �������� � �������� �� � ������������ ��������� ���
% ������ �����
function noizeCheckboxAssignin(Noize)
noize.ch9 = plot(Noize.t(:),Noize.x(:),'xg','Visible','off','DisplayName', '���� �� x');
noize.ch10 = plot(Noize.t(:),Noize.y(:),'xr','Visible','off','DisplayName', '���� �� y');
noize.ch11 = plot(Noize.t(:),Noize.z(:),'xb','Visible','off','DisplayName', '���� �� z');

assignin('base','noizePlot',noize);
