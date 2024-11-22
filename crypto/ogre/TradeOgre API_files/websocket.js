function WSConnection(){

	this.funcs_onopen = [];
	this.funcs_onclose = [];
	this.funcs_onmessage = [];
	var _this = this;
	this.start = function(host){
	
		this.conn = new WebSocket(host);
		
		this.conn.onopen = function(e){
			for(var i = 0; i < _this.funcs_onopen.length; i++){
				_this.funcs_onopen[i](this, e);
			}
		}
		
		this.conn.onclose = function(e){
			for(var i = 0; i < _this.funcs_onclose.length; i++){
				_this.funcs_onclose[i](this, e);
			}
		}
		
		this.conn.onmessage = function(e){
			for(var i = 0; i < _this.funcs_onmessage.length; i++){
				_this.funcs_onmessage[i](this, e);
			}
		}
		
	}
}

var wsconn = new WSConnection();