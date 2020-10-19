$(document).ready(() => {
  $("form#req").submit((e) => {
    $.post("submit", $("form#req").serialize(), (data, status) => {
      let resp = JSON.parse(data);
      switch(resp.error) {
        case 0:   // submitted
          let url = "/result/" + resp.ticket;
          location.href = url;
          break;
        case 1:   // empty server PoW
          alert("PoW challenge not set in session, redirecting to index.");   // PoW will be set on access to index.html
          location.reload(true);
          break;
        case 2:   // empty client PoW
          alert("PoW was not submitted.");
          break;
        case 3:   // incorrect PoW
          alert("PoW incorrect.");
          break;
        case 4:   // incorrect URL
          alert("Invalid URL. Use only characters in the whitelist.");
          break;
        case 5:   // internal error
          alert("Failed to put submission, contact admin.");
          break;
        default:
          break;
      }
    });
    e.preventDefault();
  });
});
