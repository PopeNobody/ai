#!node
const fs = require('fs');
function order_array(parts,key) {
  const res=[];
  while(true) {
    const part = parts[key];
    const children=part.children;
    const kids=children.length;
    parts[key]=null;
    res.push(part);
    if(children == null || children.length==0) {
      key=null;
      break;
    } else if ( children.length == 1 ) {
      key=children[0];
    } else {
      console.log({key});
      console.log({parts});
      throw "Too Many Kids!"
    };
  };
  return res;
};
function findNoParent(mapping) {
  var res=[];
  var keys = Object.keys(mapping);
  for(var j=0;j<keys.length;j++) {
    const key=keys[j];
    const map=mapping[key];
    if(map.parent === null) {
      res.push(key);      
    };
  };
  if(res.length!=1) {
    throw "Need  one with no parent";
  };
  return res[0];
};
function process_message(obj){
  const message=obj.message;
  if(message==null)
    return null;
  const recipient=message.recipient;
  const content=message.content;
  if(content==null)
    return null;
  const parts=content.parts;
  if(parts==null)
    return null;
  var author=message.author;
  if(author!=null) {
    if(author.name!=null){
      author=author.name;
    } else {
      // take the null if it is a null
      author=author.role;
    };
  };
  var text="";
  for(var i=0;i<parts.length;i++){
    text=text+parts[i];
  };
  if(text.length==0)
    return null;
  if(text==="Model set context updated."){
    return null;
  };
  text='"'+text+'"';
  console.log(text);
  text=JSON.parse(text);
  return {author, recipient, text};
};
if(!fs.existsSync("html")){
  fs.mkdirSync("html");
};
const files=fs.readdirSync("conv");
for( var i=0;i<files.length;i++) {
  try {
    const jfile = files[i];
    const json = require("./conv/"+jfile);
    const key = findNoParent(json.mapping);
    let arr = order_array(json.mapping,key);
    let out = [];
    for(var i=0;i<arr.length;i++){
      const res=process_message(arr[i]);
      if(res!=null)
        out.push(res);
    };
    arr = JSON.stringify(out,null,2);
    const hfile = (""+jfile).replace(".json",".html");
    fs.writeFileSync("./html/"+hfile,arr);
    break;
  } catch ( err ) {
    console.log({err});
  };
  break;
};
