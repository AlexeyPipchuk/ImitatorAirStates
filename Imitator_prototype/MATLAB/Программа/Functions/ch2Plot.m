function ch2Plot(handles, info)
% Изменение графика в соответствии чекбоксу и меню
checkbox2 = get(handles.checkbox2,'Value');
contents = get(handles.popupmenu1, 'Value');

switch contents 
    case 1
        if checkbox2 == 1 
            set(info.ch2.coordinate,'Visible','on');
        else
            set(info.ch2.coordinate,'Visible','off');
        end
    case 2
        if checkbox2 == 1 
            set(info.ch2.speed,'Visible','on');
        else
            set(info.ch2.speed,'Visible','off');
        end
    case 3
        if checkbox2 == 1 
            set(info.ch2.acceleration,'Visible','on');
        else
            set(info.ch2.acceleration,'Visible','off');
        end
end