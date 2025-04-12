document.addEventListener('DOMContentLoaded', function () {
    const menuToggle = document.querySelector('.menu-toggle');
    const menu = document.querySelector('.menu');

    menuToggle.addEventListener('click', function () {
        menuToggle.classList.toggle('active');
        menu.classList.toggle('active');
    });

    // Ferme le menu quand on clique sur un lien
    document.querySelectorAll('.menu a').forEach(link => {
        link.addEventListener('click', () => {
            menuToggle.classList.remove('active');
            menu.classList.remove('active');
        });
    });

    // Ferme le menu quand on clique en dehors
    document.addEventListener('click', (e) => {
        if (!menu.contains(e.target) && !menuToggle.contains(e.target)) {
            menuToggle.classList.remove('active');
            menu.classList.remove('active');
        }
    });
});


// Ajouter après le code existant
document.addEventListener('DOMContentLoaded', function () {
    // Gestion du chargement progressif des images
    const images = document.querySelectorAll('.gallery-item img');

    images.forEach(img => {
        img.addEventListener('load', function () {
            this.classList.add('loaded');
        });

        // Si l'image est déjà en cache
        if (img.complete) {
            img.classList.add('loaded');
        }
    });

    // Gestion du touch pour la galerie sur mobile
    let touchStartY = 0;
    const gallery = document.querySelector('.gallery');

    gallery.addEventListener('touchstart', (e) => {
        touchStartY = e.touches[0].clientY;
    }, { passive: true });

    gallery.addEventListener('touchmove', (e) => {
        const touchY = e.touches[0].clientY;
        const scrollTop = gallery.scrollTop;

        // Empêche le scroll si on est en haut ou en bas de la galerie
        if (scrollTop <= 0 && touchY > touchStartY) {
            e.preventDefault();
        }
    }, { passive: false });
});