function ch3Plot(handles, info)
% Изменение графика в соответствии чекбоксу и меню
checkbox3 = get(handles.checkbox3,'Value');
contents = get(handles.popupmenu1, 'Value');

switch contents 
    case 1
        if checkbox3 == 1 
            set(info.ch3.coordinate,'Visible','on');
        else
            set(info.ch3.coordinate,'Visible','off');
        end
    case 2
        if checkbox3 == 1 
            set(info.ch3.speed,'Visible','on');
        else
            set(info.ch3.speed,'Visible','off');
        end
    case 3
        if checkbox3 == 1 
            set(info.ch3.acceleration,'Visible','on');
        else
            set(info.ch3.acceleration,'Visible','off');
        end
end