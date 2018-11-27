% --- ����������� ������ �����, � ����������� �� ���������� �����
function setListboxes(handles)
Real = evalin('base','Real');
VOI = evalin('base','VOI');

    linesOff();
    checkboxOff(handles);
    realSize = size(Real);
    set(handles.listbox1,'String', '��������� ���� 1');
    for i = 2:realSize(2)
        strPart = char("��������� ���� " + i);
        oldStr = get(handles.listbox1,'String');
        newStr = char(oldStr, strPart);
        set(handles.listbox1,'String', newStr);
    end
    
    VoiSize = size(VOI);
    set(handles.listbox2,'String', '��� 1');
    for i = 2:VoiSize(2)
        strPart = char("��� " + i);
        oldStr = get(handles.listbox2,'String');
        newStr = char(oldStr, strPart);
        set(handles.listbox2,'String', newStr);
    end
