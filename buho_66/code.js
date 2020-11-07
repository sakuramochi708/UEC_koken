var lineToken = "xxxxxxxxxxxxxxxxx";           // LINE notifyのトークンを入力
var get_interval = 1;                          // 1分前からの新着メールを取得


// LINEに情報を送信するメソッド
function send_line(Me) {
  var payload = { 'message': Me };
  var options = {
    "method": "post",
    "payload": payload,
    "headers": { "Authorization": "Bearer " + lineToken }
  };
  UrlFetchApp.fetch("https://notify-api.line.me/api/notify", options);
}


// メールを検索して条件に適合するか調べるメソッド
function fetchContactMail() {
  var now_time = Math.floor(new Date().getTime() / 1000);  // 現在時刻を取得
  var time_term = now_time - ((60 * get_interval) + 1);    // 60*(get_interva)+1秒前までのメールを検索する

  var strTerms = '(is:unread from:"xxxxxx@gmail.com")';    // 検索条件の指定

  var myThreads = GmailApp.search(strTerms);               // 自分のGmailアカウントのスレッドから条件にあったメールを取得
  var myMsgs = GmailApp.getMessagesForThreads(myThreads);  // 条件に適合したメールのヘッダー情報を取得する
  var valMsgs = [];                                        // 情報を格納する配列を宣言

  for (var i = 0; i < myMsgs.length; i++) {                // LINEに表示する文字列を生成
    valMsgs[i] =
      " " + (parseInt(myMsgs[i].slice(-1)[0].getDate().getMonth()) + 1).toString(10) + "/" + myMsgs[i].slice(-1)[0].getDate().getDate()       // 取得日付
      + " " + myMsgs[i].slice(-1)[0].getDate().getHours() + ":" + myMsgs[i].slice(-1)[0].getDate().getMinutes()                               // 取得時間
      + "\n[from]" + myMsgs[i].slice(-1)[0].getFrom()                                                                                         // 送信者情報
      + "\n\n[subject]" + myMsgs[i].slice(-1)[0].getSubject()                                                                                 // メールのタイトル
      + "\n\n[Message]\n" + myMsgs[i].slice(-1)[0].getPlainBody()                                                                             // メールの本文
      ;

    for (var j = 0; j < myMsgs[i].length; j++) {
      myMsgs[i][j].markRead();                               // メールを既読にする
    }
  }

  return valMsgs;
}


function main() {
  new_Me = fetchContactMail()
  if (new_Me.length > 0) {
    for (var i = new_Me.length - 1; i >= 0; i--) {
      send_line(new_Me[i])
    }
  }
}
