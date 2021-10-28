// htmlに読み込ませるためのおまじない
function doGet(){
  var html = HtmlService.createTemplateFromFile('index');
  return html.evaluate(); 
}
