% --- Скрытие линий графика
function setLinesOff(inform)
    set(inform.ch1.coordinate,'Visible','off');
    set(inform.ch1.speed,'Visible','off');
    set(inform.ch1.acceleration,'Visible','off');
    
    set(inform.ch2.coordinate,'Visible','off');
    set(inform.ch2.speed,'Visible','off');
    set(inform.ch2.acceleration,'Visible','off');
    
    set(inform.ch3.coordinate,'Visible','off');
    set(inform.ch3.speed,'Visible','off');
    set(inform.ch3.acceleration,'Visible','off');

