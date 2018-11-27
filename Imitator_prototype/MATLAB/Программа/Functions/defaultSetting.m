% --- Задаются первоначальные данные графика
function defaultSetting(handles)
set(handles.uibuttongroup1,'Visible','on');
set(handles.uibuttongroup7,'Visible','on');
set(handles.uipanel3,'Visible','on');
set(handles.pushbutton3,'Visible','on');

grid on;
hold on;
xlabel('Время, s');
ylabel('Координаты, m');

Real = evalin('base','Real');
VOI = evalin('base','VOI');

allRealCheckboxAssignin(Real);
allVoiCheckboxAssignin(VOI);

realPlot = evalin('base','realPlot');
firstIndex = 1;
assignin('base','realIndex',firstIndex);
voiPlot = evalin('base','voiPlot');
assignin('base','voiIndex',firstIndex);

setListboxes(handles);

legend([realPlot(1).ch1.coordinate,realPlot(1).ch2.coordinate,realPlot(1).ch3.coordinate,...
    voiPlot(1).ch1.coordinate,voiPlot(1).ch2.coordinate,voiPlot(1).ch3.coordinate]);