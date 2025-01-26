// navbar hamburger
const hamburger = document.getElementById("hamburger");
const dropdownMenu = document.getElementById("dropdown-menu");

hamburger.addEventListener("click", () => {
    const isHidden = dropdownMenu.classList.toggle("hidden");

    if (!isHidden) {
        dropdownMenu.style.maxHeight = `${dropdownMenu.scrollHeight}px`;
    } else {
        dropdownMenu.style.maxHeight = "0";
    }
    dropdownMenu.style.transitionDuration = "0.5s";
    hamburger.classList.toggle("hidden");
});

document.addEventListener("click", (event) => {
    if (
        !hamburger.contains(event.target) &&
        !dropdownMenu.contains(event.target)
    ) {
        dropdownMenu.classList.add("hidden");
        dropdownMenu.style.maxHeight = "0";
        hamburger.classList.remove("hidden");
    }
});

//  scroll function   
document.querySelectorAll("[data-scroll-to]").forEach((btn) => {
    btn.addEventListener("click", (event) => {
        const targetId = btn.getAttribute("data-scroll-to");
        const targetElement = document.getElementById(targetId);
        if (targetElement) {
            targetElement.scrollIntoView({
                behavior: "smooth",
                block: "start",
            });
        }
    });
});


//crad tilt
VanillaTilt.init(document.querySelectorAll(".card"), {
    max: 25,
    speed: 400,
    reset: false,

});


// animate on scroll 
AOS.init();



// comparision table hidden 
document.getElementById('learnMoreButton').addEventListener('click', () => {
    const tableDiv = document.getElementById('comparisonTable');
    if (tableDiv.style.height === "0px" || !tableDiv.style.height) {
        const scrollHeight = tableDiv.scrollHeight;
        tableDiv.style.height = `${scrollHeight}px`;
    } else {
        tableDiv.style.height = "0px";
    }
});