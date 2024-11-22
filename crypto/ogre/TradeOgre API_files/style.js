var pagestyle = 'dark';

function SetStyle(style){
	pagestyle = style;
	Cookies.remove("pagestyle", {path: ''});
	Cookies.set("pagestyle", style, {expires: 365, path: '/'});
	$("#pagestyle").attr("href", "/css/" + pagestyle + ".css");
	if(typeof(trade) !== "undefined"){
		trade.SetPageStyle(style);
	}
}

$(function(){
	var cookie = Cookies.get("pagestyle");
	if(cookie){
		pagestyle = cookie;
	}
	$("#light").click(function(){
		$(this).toggleClass("lighton");
		if($(this).hasClass("lighton")){
			SetStyle("light");
		}else{
			SetStyle("dark");
		}
	});
});