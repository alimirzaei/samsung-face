$(function () {
  var model = {
    imageSources: {
      background: "/images/app/background.png",
      happyNewYear: "/images/app/happy-new-year.png",
      beAmoo: "/images/app/be-amoo-button.png",
      topLeftCard: "/images/app/egg-card.png",
      topRightCard: "/images/app/fish-card.png",
      bottomLeftCard: "/images/app/rooster-card.png",
      bottomRightCard: "/images/app/grass-card.png",
      amooCard: "/images/app/amoo-card.png",
      samsung: "/images/app/samsung.png"
    }
  };

  var controller = {
    init: function () {
      view.init();
      cameraView.init();
    },
    getImageSources: function () {
      return model.imageSources;
    },
    processImage: function () {
      view.$fileInput.parent().submit();
      // TODO: add if for handling desktop web based camera
    }
  };

  var view = {
    cacheDom: function () {
      this.$happyNewYear = $("#happy-new-year");
      this.$happyNewYearImage = $("#happy-new-year-text");
      this.$beAmooButtonImage = $("#be-amoo");
      this.$topLeftCardImage = $("#top-left-card");
      this.$topRightCardImage = $("#top-right-card");
      this.$bottomLeftCardImage = $("#bottom-left-card");
      this.$bottomRightCardImage = $("#bottom-right-card");
      this.$amooCardImage = $("#amoo-card");
      this.$samsungImage = $("#samsung");
      this.$fileInput = $("#file-input");
      this.$cameraOpenButton = $("#camera-open-button");
      this.$cameraModal = $("#camera-modal");
    },
    bindEvents: function () {
      this.$topLeftCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/1";
      });
      this.$topRightCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/2";
      });
      this.$bottomLeftCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/3";
      });
      this.$bottomRightCardImage.on("click", function () {
        // TODO: change image to images
        window.location.href="image/4";
      });

      this.$amooCardImage.on("click", function () {
        view.$fileInput.click();
      });

      this.$fileInput.on("change", controller.processImage);

      this.$cameraOpenButton.on("click", function () {
        view.$cameraModal.css("display", "block");
        controller.openCamera();
      });

    },
    init: function () {
      this.cacheDom();
      this.bindEvents();
      this.render();
    },
    render: function () {
      this.$happyNewYear.parent().css("background-image", 'url(' + controller.getImageSources().background + ')');
      this.$happyNewYear.parent().css("background-size", '100% 100%');
      // this.$happyNewYearImage.attr("src", controller.getImageSources().happyNewYear);
      this.$beAmooButtonImage.attr("src", controller.getImageSources().beAmoo);
      this.$topLeftCardImage.attr("src", controller.getImageSources().topLeftCard);
      this.$topRightCardImage.attr("src", controller.getImageSources().topRightCard);
      this.$bottomLeftCardImage.attr("src", controller.getImageSources().bottomLeftCard);
      this.$bottomRightCardImage.attr("src", controller.getImageSources().bottomRightCard);
      this.$amooCardImage.attr("src", controller.getImageSources().amooCard);
      this.$samsungImage.attr("src", controller.getImageSources().samsung);
    }
  };

  var cameraView = {
    cacheDom: function () {
      this.$snapshotButton = $("#camera-snapshot-button");
      this.$closeButton = $("#camera-close-button");
      this.$processButton = $("#camera-process-button");
    },
    bindEvents: function () {
      this.$snapshotButton.on("click", function () {
        controller.takeSnapshot();
      });
      this.$closeButton.on("click", function () {
        view.$cameraModal.css("display", "none");
      });
      this.$processButton.on("click", function () {
        controller.processImage();
      });
    },
    init: function () {
      this.cacheDom();
      this.bindEvents();
      this.render();
    },
    render: function () {

    }
  };

  controller.init();
});
