function allVoiCheckboxAssignin(Voi)

voiSize = size(Voi);
cmap = hsv(voiSize(2)*6);
for i = 1:voiSize(2)
    voi(i).ch1.coordinate = plot(Voi(i).t(:),Voi(i).x(:),'-.s','Color',cmap(i*4,:),...
        'Visible','off','DisplayName', '��� x');
    voi(i).ch1.speed = plot(Voi(i).t(:),Voi(i).Vx(:),'-.s','Color',cmap(i*4,:),...
        'Visible','off','DisplayName', '��� V(x)');
    voi(i).ch1.acceleration = plot(Voi(i).t(:),Voi(i).ax(:),'-.s','Color',cmap(i*4,:),...
        'Visible','off','DisplayName', '��� a(x)');

    voi(i).ch2.coordinate = plot(Voi(i).t(:),Voi(i).y(:),'-.s','Color',cmap(i*5,:),...
        'Visible','off','DisplayName', '��� y');
    voi(i).ch2.speed = plot(Voi(i).t(:),Voi(i).Vy(:),'-.s','Color',cmap(i*5,:),...
        'Visible','off','DisplayName', '��� V(y)');
    voi(i).ch2.acceleration = plot(Voi(i).t(:),Voi(i).ay(:),'-.s','Color',cmap(i*5,:),...
        'Visible','off','DisplayName', '��� a(y)');

    voi(i).ch3.coordinate = plot(Voi(i).t(:),Voi(i).z(:),'-.s','Color',cmap(i*6,:),...
        'Visible','off','DisplayName', '��� z');
    voi(i).ch3.speed = plot(Voi(i).t(:),Voi(i).Vz(:),'-.s','Color',cmap(i*6,:),...
        'Visible','off','DisplayName', '��� V(z)');
    voi(i).ch3.acceleration = plot(Voi(i).t(:),Voi(i).az(:),'-.s','Color',cmap(i*6,:),...
        'Visible','off','DisplayName', '��� a(z)');
end

legend Off;

assignin('base','voiPlot',voi);