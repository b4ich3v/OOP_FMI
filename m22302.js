
//	Основи на Компютърната Графика
//	Модел 22302 - Дърво от папратово листо
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22302 = function M22302(room)
{
	MEIRO.Model.apply(this, arguments);

	this.n = options.lowpoly?6:9;
	this.tree = new THREE.LineSegments( new THREE.Geometry(), new THREE.LineBasicMaterial( {color: 'firebrick'}) );
	this.tree.rotation.set(-Math.PI/2,-Math.PI/2,0);
	this.leaves = new THREE.LineSegments( new THREE.Geometry(), new THREE.LineBasicMaterial( {color: 'green'}) );
	this.leaves.rotation.set(-Math.PI/2,-Math.PI/2,0);
	this.generateFern(this.n);
		
	// бутон за превключване
	var that = this;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'НАНОВО', 'images/random.png');
	this.toggle.hide();

	// сглобяване на целия модел
	this.image.add(this.tree,this.leaves);
}

MEIRO.Models.M22302.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22302.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22302.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22302.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22302.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22302.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Дърво от папратово листо</h1>';

	s += '<p>Този фрактал има същата конструкция както и папратовото листо. Разликата е в ъглите между отделните отсечки и коефициентите на скъсяването им.  Поради случайността в избора на ъгли, някои дървета могат да се генерират по-красиви, а други &ndash; по-грозновати.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22302.prototype.generateFern = function(level)
{
	var len = 1.75,
		nt = 0,
		nl = 0,
		tree = this.tree,
		leaves = this.leaves,
		that = this;

	var turtle = new MEIRO.Turtle(0);
	turtle.setPosition(new THREE.Vector3(-2*len,0,0));
	
	
	function genTree(len,level,isMain)
	{
		var hCurve = THREE.Math.randFloat(-1,1)*(isMain?5:30);
		var vCurve = THREE.Math.randFloat(-1,1)*(isMain?5:30);
		var zCurve = THREE.Math.randFloat(0,2*Math.PI);

		if (level<4)
		{
			leaves.geometry.vertices[nl++] = turtle.getPosition();
			turtle.fd(len);
			leaves.geometry.vertices[nl++] = turtle.getPosition();
		}
		else
		{
			tree.geometry.vertices[nt++] = turtle.getPosition();
			turtle.fd(len);
			tree.geometry.vertices[nt++] = turtle.getPosition();
		}
		
		if (level)
		{
			var basis = turtle.basis.clone();

			// ляво подлисто
			turtle.lt(60);
			turtle.upp(zCurve);
			turtle.lr(90);
			genTree(len*0.5,level-1);
			
			// дясно подлисто
			turtle.basis.copy(basis);
			turtle.rt(60);
			turtle.upp(zCurve);
			turtle.lr(90);
			genTree(len*0.5,level-1);

			// продължение на листото
			turtle.basis.copy(basis);
			turtle.lr(90);
			turtle.lt(hCurve);
			turtle.dn(vCurve);
			genTree(len*0.8,level-1,true);
		}
	}
	
	genTree(len,level,true);
	tree.geometry.verticesNeedUpdate = true;
	leaves.geometry.verticesNeedUpdate = true;
}


// превключвател на модела
MEIRO.Models.M22302.prototype.onToggle = function(element)
{
	this.generateFern(this.n);

	reanimate();
}
	