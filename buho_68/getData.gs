//データ取得
function getData() {  
  // 研究室と番号対応表
  var labnum = [
    "集合教室",    // 0
    // 27研究室ありました
  ];

  // 状態対応表
  var kindnum = [
    "訪問開始",
    "訪問終了",
    "通過",
    "受付",
    "終了"
  ];

  //データ取得するシート
  // https://docs.google.com/spreadsheets/d/xxxxxxxxxxxxxx/edit#gid=0000000 の xxxxxの部分をコピー
  let spreadsheetID = "xxxxxxxxxxxxxxxx"
  let sheetID = "formanswer"
  var sheet = SpreadsheetApp.openById(spreadsheetID).getSheetByName(sheetID);

  //行（横軸）と列（縦軸）の最大数を取得
  var maxRow = sheet.getLastRow();
  var maxColumn = sheet.getLastColumn();

  //JSON用のkey
  var keys = [];

  //データ格納配列
  var data = [];

  //1行目のkeyの名前取得
  //JSON用のラベルは1行目で指定しているため
  //【getRange】の第1引数は【1】
  for (var x = 1; x <= maxColumn; x++) {
    keys.push(sheet.getRange(1, x).getValue());
  }
  
  //データの取得
  //実際のデータが2行目からなので【y = 2】から開始
  //getRange()を使って、2行目1セル ～ 最終行目の最終セルを範囲指定
  // getRange(x, y, xからa列分, yからb列分)
  var _values = sheet.getRange(2, 1, maxRow-1, maxColumn).getValues();

  // jsonの形式に値を調整する
  for(var i = 0; i < _values.length; i++){

    // spreadsheetにある回答を削除したときの例外処理
    if(_values[i][0] == ''){
      continue;
    }
    // 学生以外の人が入力したときの例外処理(1x代、2x代にしか対応しない)
    if(_values[i][1].substr(1,1) != "1" && _values[i][1].substr(1,1) != "2"){
      continue;
    }

    var json = {};

    // 1列目：timestampを秒(UTC)に
    let date = new Date(_values[i][0]);
    let time = date.getTime(); // ミリ秒表示
    time = parseInt(time / 1000);
    time = time % 1000000;
    json[keys[0]] = time;

    // 2列目: uec glメールから学籍番号を抽出（文字列）
    json[keys[1]] = (_values[i][1]).substr(1, 7);


    // 3列目: チェックポイント（日本語・文字列）
    var a;
    for(a = 0; a < labnum.length; a++){
      if(_values[i][2] == labnum[a]){
        break;
      }
    }
    // 4列目: チェックの状態（日本語・文字列）
    var b;
    for(b = 0; b < kindnum.length; b++){
      if(_values[i][3] == kindnum[b]){
        break;
      }
    }

//////////// json 値設定 ///////////////

    if(b >= 3){ // 受付 or 終了の場合
      json[keys[2]] = 0;
    }else if(b == 0){ // 訪問開始の場合
      json[keys[2]] = a;
    }else if(b == 1){ // 訪問終了の場合
      json[keys[2]] = a + 0.1;
    }else{ // 通過の場合（何も考えていない）
      json[keys[2]] = a + (b / 10.0);
    }

///////////////////////////////////////
    data.push(json);
  }

  //整形してテキストに
  Logger.log(JSON.stringify(data , null, '\t'));
  return JSON.stringify(data , null, '\t');  
}
