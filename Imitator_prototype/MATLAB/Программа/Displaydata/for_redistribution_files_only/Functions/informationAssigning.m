% --- К рабочей среде привязыаются данные из файла
function informationAssigning(name, path_my)
    path(path,path_my);
    file = load (name);
    % --- Проверка на наличие эталоных данных в файле
    if isfield(file,'Real')
        assignin('base','Real',file.Real);
    else
        makeEmptyReal();
    end
    % --- Проверка на наличие данных ВОИ в файле
    if isfield(file,'VOI')
        assignin('base','VOI',file.VOI);
    else
        makeEmptyVOI();
    end
    % --- Проверка на наличие данных ПОИ в файле
    if isfield(file,'POI')
        assignin('base','POI',file.POI);
    else
        makeEmptyPOI();
    end
    % --- Проверка на наличие данных шума в файле
    if isfield(file,'Noize')
        assignin('base','Noize',file.Noize);
    else
        makeEmptyNoize();
    end
    % --- Проверка на наличие данных строба в файле
    if isfield(file,'Strob')
        assignin('base','Strob',file.Strob);
    else
        makeEmptyStrob();
    end