% --- �������� �������� � �������� �� � ������������ ��������� ���
% ������ ������
function strobCheckboxAssignin(Strob)
strob.ch13 = errorbar(Strob.t(:),Strob.x(:),Strob.Sx(:),...
    'dg','Visible','off','DisplayName', '������ �� x');
strob.ch14 = errorbar(Strob.t(:),Strob.y(:),Strob.Sy(:),...
    'dr','Visible','off','DisplayName', '������ �� y');
strob.ch15 = errorbar(Strob.t(:),Strob.z(:),Strob.Sz(:),...
    'db','Visible','off','DisplayName', '������ �� z');

assignin('base','strobPlot',strob);