
//	Основи на Компютърната Графика
//	Модел 22262 - Оцветен планински терен
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22262 = function M22262(room)
{
	MEIRO.Model.apply(this, arguments);

	var models = (options.models||options.model||'').split(',');
	if (models.length==1)
	{
		this.n = options.lowpoly?6:9;
		this.m = options.lowpoly?32:256;
	}
	else
	{
		this.n = options.lowpoly?5:7;
		this.m = options.lowpoly?16:64;
	}
	
	this.terrain = new THREE.Mesh(
		new THREE.PlaneGeometry(14,14,this.m,this.m),
		new THREE.MeshLambertMaterial({color:'cornflowerblue',vertexColors: THREE.VertexColors,side:THREE.DoubleSide})
	);
	this.terrain.rotation.x = -Math.PI/2;
	
	var light = new THREE.AmbientLight('white',1/2);
	light.position.set(0,5,0);
	
	var water = new THREE.Mesh(
		new THREE.PlaneGeometry(14,14),
		new THREE.MeshBasicMaterial({color:'navy',transparent:true,opacity:0.6,side:THREE.DoubleSide})
	);
	water.rotation.x = -Math.PI/2;
	
	// бутон за превключване
	var that = this;
	this.state = this.n-1;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'НИВО', 'images/n123n.png');
	this.toggle.hide();
	this.toggle.button.onclick();

	// сглобяване на целия модел
	this.image.add(light,water,this.terrain);
}

MEIRO.Models.M22262.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22262.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22262.POS = {DIST:15, ROT_X:0.4, ROT_Y:0.5};
MEIRO.Models.M22262.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22262.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22262.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Оцветен планински терен</h1>';

	s += '<p>Цветът на терена се определя от височината на всекъ връх от него. Върховете под морксото равнище се оцветяват от синьо към черно, тези на морското равнище са жълтеникаво, а тези, които са над него преминават от зелено през оранжево до бяло.</p>';
	
	element.innerHTML = s;
}


// превключвател на модела
MEIRO.Models.M22262.prototype.onToggle = function(element)
{
	this.state = (this.state+1)%this.n;
	this.toggle.setText('НИВО №'+this.state+' от '+(this.n-1));
	
	var geometry = this.terrain.geometry;
	var vertices = geometry.vertices;
	var m = this.m;
	
	function add(u,v,value)
	{
		vertices[u+(m+1)*v].z += value;
	}

	function set(u,v,value)
	{
		vertices[u+(m+1)*v].z = value;
	}

	function color(z)
	{
		function f(x,x1,x2,y1,y2 )
		{
			return ( x-x1 )/( x2-x1 )*( y2-y1 )+y1;
		}

		var K = -4/2;	// ниво на черен цвят
		var B = -1/2;		// ниво на син цвят
		var Y = 0.2/2;		// на жълт цвят
		var G = 1/2;		// на зелен
		var R = 2.5/2;		// оранжев
		var W = 4.5/2;		// бял

		// интерполиране на цвета според височината z
		if( z<K ) return new THREE.Color(0,0,0);	// 0,0,0
		if( (K<=z) && (z<B) ) return new THREE.Color( 0,0,f( z,K,B,0,1 ) );	// 0,0,0 -> 0,0,1
		if( (B<=z) && (z<Y) ) return new THREE.Color( f( z,B,Y,0,1 ),f( z,B,Y,0,1 ),f( z,B,Y,1,0 ) ); //0,0,1 -> 1,1,0
		if( (Y<=z) && (z<G) ) return new THREE.Color( f( z,Y,G,1,0 ),f( z,Y,G,1,1 ),f( z,Y,G,0,0 ) ); //1,1,0 -> 0,1,0
		if( (G<=z) && (z<R) ) return new THREE.Color( f( z,G,R,0,1 ),f( z,G,R,1,0.5 ),f( z,G,R,0,0 ) ); // 0,1,0 -> 1,0.5,0
		if( (R<=z) && (z<W) ) return new THREE.Color( f( z,R,W,1,1 ),f( z,R,W,0.5,1 ),f( z,R,W,0,1 ) ); //1,0.5,0 -> 1,1,1
		return new THREE.Color(1,1,1);
	}
			
	var count = Math.pow(2,this.state)+1;
	var step = this.m/(count-1);
	var rand = 5*Math.pow(0.5,this.state);
	
	if (this.state==0)
	{
		for (var i=0; i<vertices.length; i++)
			vertices[i].z = 0.5;
	}
	else
	{
		// издигане на избрани точки
		for (var i=0; i<count; i++)
		for (var j=0; j<count; j++)
		{
			var u = i*step;
			var v = j*step;
			add(u,v,THREE.Math.randFloat(-rand,rand));
		}
		/*
		set(0,0,0);
		set(m,0,0);
		set(m,m,0);
		set(0,m,0);
		*/
		// издигане на междинните точки
		for (var i=0; i<count-1; i++)
		for (var j=0; j<count-1; j++)
		{
			var u1 = i*step;
			var v1 = j*step;
			var u2 = (i+1)*step;
			var v2 = (j+1)*step;

			var z11 = vertices[u1+(m+1)*v1].z;
			var z12 = vertices[u1+(m+1)*v2].z;
			var z21 = vertices[u2+(m+1)*v1].z;
			var z22 = vertices[u2+(m+1)*v2].z;
			
			for (var ii=0; ii<=step; ii++)
			for (var jj=0; jj<=step; jj++)
			{
				var ku = ii/step;
				var kv = jj/step;
				var value = z11*(1-ku)*(1-kv) + z21*ku*(1-kv) + z22*ku*kv + z12*(1-ku)*kv;
				set(u1+ii,v1+jj,value);
			}
		}
	}
	
	for (var f = 0; f<geometry.faces.length; f++)
	{
		geometry.faces[f].vertexColors[0] = color( vertices[geometry.faces[f].a].z );
		geometry.faces[f].vertexColors[1] = color( vertices[geometry.faces[f].b].z );
		geometry.faces[f].vertexColors[2] = color( vertices[geometry.faces[f].c].z );
	}

	geometry.verticesNeedUpdate = true;
	geometry.elementsNeedUpdate = true;
	geometry.computeVertexNormals();
	
	reanimate();
}
	