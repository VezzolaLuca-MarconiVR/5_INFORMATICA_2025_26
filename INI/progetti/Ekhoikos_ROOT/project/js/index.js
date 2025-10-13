const peelElements = document.querySelectorAll('.peel-text');

peelElements.forEach(element => {
  element.addEventListener('click', function () {
    this.classList.toggle('peeled');
    this.parentElement.classList.toggle('peeled');
  });
});
