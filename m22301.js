
//	Основи на Компютърната Графика
//	Модел 22301 - Папратово листо
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22301 = function M22301(room)
{
	MEIRO.Model.apply(this, arguments);

	this.n = options.lowpoly?7:10;
	this.fern =	new THREE.LineSegments( new THREE.Geometry(), new THREE.LineBasicMaterial( {color: 'black'}) );
	this.fern.rotation.set(-Math.PI/2,-Math.PI/2,0);
	this.generateFern(this.n);
		
	// бутон за превключване
	var that = this;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'НАНОВО', 'images/random.png');
	this.toggle.hide();

	// сглобяване на целия модел
	this.image.add(this.fern);
}

MEIRO.Models.M22301.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22301.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22301.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22301.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22301.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22301.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Папратово листо</h1>';

	s += '<p>Фракталната реализация на папратово листо използва себеподобието на фракталите. Фрагмент от листото се генерира по същия начин както и цялото листо. За постигане на по-естествена форма се използват три ъгъла: единият определя огъването на листото наляво-надясно, вторият е за огъването напред-назад (това създава тримерност) и третият е ъгълът на подлистата спрямо стъблото (това прави стъблото да е леко "вдлъбнато" спрямо повърхността на листото).</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22301.prototype.generateFern = function(level)
{
	var len = 2,
		n = 0,
		fern = this.fern;

	var turtle = new MEIRO.Turtle(0);
	turtle.setPosition(new THREE.Vector3(-2*len,0,0));
	
	var hCurve = THREE.Math.randFloat(-15,15);
	var vCurve = THREE.Math.randFloat(-20,20);
	var zCurve = THREE.Math.randFloat(0,vCurve/2);
	
	function tree(len,level)
	{
		fern.geometry.vertices[n++] = turtle.getPosition();
		turtle.fd(len);
		fern.geometry.vertices[n++] = turtle.getPosition();

		if (level)
		{
			var basis = turtle.basis.clone();

			// ляво подлисто
			turtle.lt(45);
			turtle.upp(zCurve);
			tree(len*0.4,level-1);
			
			// дясно подлисто
			turtle.basis.copy(basis);
			turtle.rt(45);
			turtle.upp(zCurve);
			tree(len*0.4,level-1);
			
			// продължение на листото
			turtle.basis.copy(basis);
			turtle.lt(hCurve);
			turtle.dn(vCurve);
			tree(len*0.8,level-1);
		}
	}
	
	tree(len,level);
	fern.geometry.verticesNeedUpdate = true;
}


// превключвател на модела
MEIRO.Models.M22301.prototype.onToggle = function(element)
{
	this.generateFern(this.n);

	reanimate();
}
	