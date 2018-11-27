function ch1Plot(handles, info)
% Изменение графика в соответствии чекбоксу и меню
checkbox1 = get(handles.checkbox1,'Value');
contents = get(handles.popupmenu1, 'Value');

switch contents 
    case 1
        if checkbox1 == 1 
            set(info.ch1.coordinate,'Visible','on');
        else
            set(info.ch1.coordinate,'Visible','off');
        end
    case 2
        if checkbox1 == 1 
            set(info.ch1.speed,'Visible','on');
        else
            set(info.ch1.speed,'Visible','off');
        end
    case 3
        if checkbox1 == 1 
            set(info.ch1.acceleration,'Visible','on');
        else
            set(info.ch1.acceleration,'Visible','off');
        end
end
