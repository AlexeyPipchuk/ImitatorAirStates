% --- � ������� ����� ������������ ������ �� �����
function informationAssigning(name, path_my)
    path(path,path_my);
    file = load (name);
    % --- �������� �� ������� �������� ������ � �����
    if isfield(file,'Real')
        assignin('base','Real',file.Real);
    else
        makeEmptyReal();
    end
    % --- �������� �� ������� ������ ��� � �����
    if isfield(file,'VOI')
        assignin('base','VOI',file.VOI);
    else
        makeEmptyVOI();
    end
    % --- �������� �� ������� ������ ��� � �����
    if isfield(file,'POI')
        assignin('base','POI',file.POI);
    else
        makeEmptyPOI();
    end
    % --- �������� �� ������� ������ ���� � �����
    if isfield(file,'Noize')
        assignin('base','Noize',file.Noize);
    else
        makeEmptyNoize();
    end
    % --- �������� �� ������� ������ ������ � �����
    if isfield(file,'Strob')
        assignin('base','Strob',file.Strob);
    else
        makeEmptyStrob();
    end