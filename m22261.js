
//	Основи на Компютърната Графика
//	Модел 22261 - Формиране на планински терен
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22261 = function M22261(room)
{
	MEIRO.Model.apply(this, arguments);

	this.n = options.lowpoly?6:8;
	this.m = options.lowpoly?32:128;
	
	this.terrain = new THREE.Mesh(
		new THREE.PlaneGeometry(12,12,this.m,this.m),
		new THREE.MeshBasicMaterial({color:'black',wireframe:true,transparent:true,opacity:0.3,depthTest:false})
	);
	this.terrain.rotation.x = Math.PI/2;
	
	// бутон за превключване
	var that = this;
	this.state = this.n-1;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'НИВО', 'images/n123n.png');
	this.toggle.hide();
	this.toggle.button.onclick();

	// сглобяване на целия модел
	this.image.add(this.terrain);
}

MEIRO.Models.M22261.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22261.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22261.POS = {DIST:15, ROT_X:0.4, ROT_Y:0.5};
MEIRO.Models.M22261.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22261.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22261.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Формиране на планински терен</h1>';

	s += '<p>Постъпковото генериране на този фракрал раздробява първоначалната форма на четири по-малки, после всяка от тях на още четири и т.н. На всяка стъпка се променя височината на върховете на формите &ndash; може да се издигне или да се сниши.</p>';
	
	element.innerHTML = s;
}


// превключвател на модела
MEIRO.Models.M22261.prototype.onToggle = function(element)
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

	var count = Math.pow(2,this.state)+1;
	var step = this.m/(count-1);
	var rand = 5*Math.pow(0.5,this.state);
	
	if (this.state==0)
	{
		for (var i=0; i<vertices.length; i++)
			vertices[i].z = 0;
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
		
		set(0,0,0);
		set(m,0,0);
		set(m,m,0);
		set(0,m,0);
		
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
	geometry.verticesNeedUpdate = true;
	
	reanimate();
}
	