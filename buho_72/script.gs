// Discord 側へメッセージを送る
function send_notify_to_discord(message){

  // webhook置き場
  const DISCORD_WEBHOOK = "Here is Discord Token"


  // Discordへメッセージを送信する本体 
  const payload = {
    username: "Here is Discord webhook bot name",
    content: message
  }


  // Discordに送信する型を指定（おまじない）
  UrlFetchApp.fetch(DISCORD_WEBHOOK, {
    method: "post",
    contentType: "application/json",
    payload: JSON.stringify(payload),
  });

}


// 新規メールを取得して、必要情報を抽出する関数
function fetch_new_arrival_mail(interval){
  start_period = setting_start_of_search_mail_period();
  search_criteria = setting_search_criteria(interval);

  // 取得
  let myThreads = GmailApp.search(search_criteria);
  let myMsgs = GmailApp.getMessagesForThreads(myThreads);
  let valMsgs = [];

  // メッセージ解析
  for(var i = 0; i < myMsgs.length; i++){
    // 添付ファイルがあるかどうか
    function is_exist_attachment_file() {
      if(myMsgs[i].slice(-1)[0].getAttachments() != ""){
        return "\n添付ファイルがあります！メール本体の確認をお忘れなく";
      }else{
        return " ";
      } 
    } 

    // 本文メッセージ
    let message_plain_text = myMsgs[i].slice(-1)[0].getPlainBody();

    // 文字数が1700文字を超えていないかチェック
    function is_length_over_1700(){
      if(message_plain_text.length > 1700){
        return "\n文字数が多すぎます！メール本体で確認してください。";
      }else{
        return " ";
      }
    }

    // 文字数が1700文字超えていない時に本文を展開
    function open_mailbody(){
      if(message_plain_text.length <= 1700){
        let msg = "\n[Message]\n" + message_plain_text;
        return msg;
      }else{
        return " ";
      }
    }

    valMsgs[i] = 
      "メッセージが届きました！"
      + is_exist_attachment_file()
      + is_length_over_1700()
      + "\n```txt"
      + "\n[Date] " + myMsgs[i].slice(-1)[0].getDate()
      + "\n[from] " + myMsgs[i].slice(-1)[0].getFrom() // from情報
      + "\n[to] "   + myMsgs[i].slice(-1)[0].getTo()   // to情報
      + "\n[cc] "   + myMsgs[i].slice(-1)[0].getCc()   // cc情報
      + "\n[subject] " + myMsgs[i].slice(-1)[0].getSubject() // 件名情報
      + open_mailbody()  // 本文情報
      + "```\n"
  }

  return valMsgs;
}

// 検索する時間の開始地点を設定
function setting_start_of_search_mail_period(){
  // 今回は61秒前を設定
  let now_time = Math.floor(new Date().getTime() / 1000);
  let time_term = now_time - ((60 * 1) + 1);
  return time_term;
}

// メールの検索条件を設定
// 詳しくはここ => https://support.google.com/mail/answer/7190?hl=ja
function setting_search_criteria(interval){
  let strTerms = 'is:unread after:' + interval;
  // let strTerms = 'is:unread';
  return strTerms;
}

// 実行してもらうのはこれ
function main() {
  new_Me =  fetch_new_arrival_mail(setting_start_of_search_mail_period())
  if(new_Me.length > 0){
    for(var i = new_Me.length-1; i >= 0; i--){
      send_notify_to_discord(new_Me[i])
    }
  }
}
