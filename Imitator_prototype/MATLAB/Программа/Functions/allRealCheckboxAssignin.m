% --- �������� �������� � �������� �� � ������������ ��������� ���
% ��������� ������
function allRealCheckboxAssignin(Real)

realSize = size(Real);
cmap = hsv(realSize(2)*6);
for i = 1:realSize(2)
    real(i).ch1.coordinate = plot(Real(i).t(:),Real(i).x(:),'-o','Color',cmap(i,:),...
        'Visible','off','DisplayName', '������ x');
    real(i).ch1.speed = plot(Real(i).t(:),Real(i).Vx(:),'-o','Color',cmap(i,:),...
        'Visible','off','DisplayName', '������ V(x)');
    real(i).ch1.acceleration = plot(Real(i).t(:),Real(i).ax(:),'-o','Color',cmap(i,:),...
        'Visible','off','DisplayName', '������a(x)');

    real(i).ch2.coordinate = plot(Real(i).t(:),Real(i).y(:),'-o','Color',cmap(i*2,:),...
        'Visible','off','DisplayName', '������ y');
    real(i).ch2.speed = plot(Real(i).t(:),Real(i).Vy(:),'-o','Color',cmap(i*2,:),...
        'Visible','off','DisplayName', '������ V(y)');
    real(i).ch2.acceleration = plot(Real(i).t(:),Real(i).ay(:),'-o','Color',cmap(i*2,:),...
        'Visible','off','DisplayName', '������ a(y)');

    real(i).ch3.coordinate = plot(Real(i).t(:),Real(i).z(:),'-o','Color',cmap(i*3,:),...
        'Visible','off','DisplayName', '������ z');
    real(i).ch3.speed = plot(Real(i).t(:),Real(i).Vz(:),'-o','Color',cmap(i*3,:),...
        'Visible','off','DisplayName', '������ V(z)');
    real(i).ch3.acceleration = plot(Real(i).t(:),Real(i).az(:),'-o','Color',cmap(i*3,:),...
        'Visible','off','DisplayName', '��a��� a(z)');
end

legend Off;

assignin('base','realPlot',real);
