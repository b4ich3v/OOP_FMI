
//	Основи на Компютърната Графика
//	Модел 22232 - Драконов лабиринт
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22232 = function M22232(room)
{
	MEIRO.Model.apply(this, arguments);

	this.k = 0;
	
	this.level = options.lowpoly?6:9;
	this.curve = [];
	this.curve.push(this.generateDragonCurve(this.level));
	for (var i=1; i<4; i++)
	{
		this.curve[i] = new THREE.Mesh(this.curve[0].geometry,this.curve[0].material);
		this.curve[i].rotation.y = i*Math.PI/2;
	}
	
	// сглобяване на целия модел
	for (var i=0; i<4; i++)
		this.image.add(this.curve[i]);
}

MEIRO.Models.M22232.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22232.DIST = {MIN:5, MAX:20, HEIGHT:-1};
MEIRO.Models.M22232.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22232.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22232.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22232.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Драконов лабиринт</h1>';

	s += '<p>Драконовият лабиринт е съставен от четири леко изместени драконови криви със скосени ръбове. Така лабиринтът се разделя на четири симетрични зони. От всяка точка на лабиринта може да се достигне до всяка друга. Ако пътят минава от една зона в друга, това може да стане само през центъра на лабиринта &ndash; там "започват" четирите драконови криви.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22232.prototype.generateDragonCurve = function(level)
{
	var len = 0.4,
		n = 0,
		dir = 0;

	var turtle = new MEIRO.Turtle(0);
	var plane = new THREE.BoxGeometry(1,1,0.1);//new THREE.PlaneGeometry(1,1);
	var material = new THREE.MeshPhongMaterial({vertexColors:THREE.VertexColors,shininess:100});
	var geometry = new THREE.Geometry();
	
	function lt(angle)
	{
		turtle.lt(angle);
		dir += angle*Math.PI/180;
	}
	
	function fd(len)
	{
		n++;
		turtle.fd(len/2);
		
		var wall = new THREE.Mesh(plane,material);
		var h = 0.3;
		wall.scale.set(len+0.042,h,1);
		wall.position.copy(turtle.basis.o);
		wall.position.y = h/2;
		wall.rotation.y = dir;
		turtle.fd(len/2);
		
		//curve.add(wall);
		geometry.mergeMesh(wall);
	}
	
	function cell(swap)
	{
		fd(len/3);
		lt(45*swap);

		fd(len);
		lt(45*swap);
		
		fd(len/3);
	}
	
	function dragon(level,swap)
	{
		if (level)
		{
			dragon( level-1,+swap );
			cell(swap);
			nogard( level-1,-swap );
		}
	}
	
	function nogard(level,swap)
	{
		if (level)
		{
			dragon( level-1,-swap );
			cell(swap);
			nogard( level-1,+swap );
		}
	}
		
	dragon(level,1);

	geometry.translate(len,0,0);
	
	var faceIndices = ['a','b','c'];
	geometry.faces.forEach(function(face)
		{
			for (var i = 0; i < 3; i++)
			{
				var vertexIndex = face[faceIndices[i]];
				var vertex = geometry.vertices[vertexIndex];
				var d = vertex.length();
				face.vertexColors[i] = new THREE.Color().setHSL(0.5+0.5*Math.cos(d/2),1,0.5);
			}
		});		

		var curve = new THREE.Mesh(geometry,material);
	return curve;
}