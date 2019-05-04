# Contributing to WowStack projects

Want to hack on [WowStack][wowstack]? Awesome!

This page contains information about reporting issues as well as some tips and
guidelines useful to experienced contributors.

## Topics

- [Reporting security sssues](#reporting-security-issues)
- [Reporting other issues](#reporting-other-issues)
- [Quick contribution tips and guidelines](#quick-contribution-tips-and-guidelines)

## Reporting security issues

The WowStack maintainers take security seriously. If you discover a security
issue, please bring it to their attention right away!

Please **DO NOT** file an issue, instead send your report to our team
[privately][security-issues]. Security reports are greatly appreciated!

## Reporting other issues

A great way to contribute to the project is to send a detailed report when you
encounter an issue. We always appreciate a well-written, thorough bug report,
and will thank you for it!

Check that [our issue database][project-issues] doesn't already include that
problem or suggestion before submitting an issue.

If you find a match, you can use the "subscribe" button to get notified on
updates. Do _not_ leave random "+1" or "I have this too" comments, as they
only clutter the discussion, and don't help resolving it. However, if you
have ways to reproduce the issue or have additional information that may help
resolving the issue, please leave a comment.

## Quick contribution tips and guidelines

This section gives the experienced contributor some tips and guidelines.

### Pull requests are always welcome

Not sure if that typo is worth a pull request? Found a bug and know how to fix
it? Do it! We will appreciate it. Any significant improvement should be
documented as [an issue][project-issues] before anybody starts working on it.

We are always thrilled to receive pull requests. We do our best to process them
quickly. If your pull request is not accepted on the first try, do not get
discouraged!

### Design and cleanup proposals

You can propose new designs for existing features. You can also design entirely
new features. We really appreciate contributors who want to refactor or
otherwise cleanup our project. For information on making these types of
contributions, see the advanced contribution section in the contributors guide.

We try hard to keep WowStack lean and focused. WowStack can't do everything
for everybody. This means that we might decide against incorporating a new
feature. However, there might be a way to implement that feature _on top of_ an
existing feature.

### Conventions

Fork the repository and make changes on your fork in a feature branch:

- If it's a bug fix branch, name it XXXX-something where XXXX is the number of
  the issue.
- If it's a feature branch, create an enhancement issue to announce
  your intentions, and name it XXXX-something where XXXX is the number of the
  issue.

Submit unit tests for your changes, we have a great test framework built in;
use it! Take a look at existing tests for inspiration. Run the full test suite
on your branch before submitting a pull request.

Update the documentation when creating or modifying features. Test your
documentation changes for clarity, concision, and correctness, as well as a
clean documentation build.

Write clean code. Universally formatted code promotes ease of writing, reading,
and maintenance. Always run the included code formatters on each changed file
before committing your changes. Most editors have plug-ins that do this
automatically.

Pull request descriptions should be as clear as possible and include a reference
to all the issues that they address.

Commit messages must start with a capitalized and short summary (max. 50 chars)
written in the imperative, followed by an optional, more detailed explanatory
text which is separated from the summary by an empty line.

Code review comments may be added to your pull request. Discuss, then make the
suggested modifications and push additional commits to your feature branch. Post
a comment after pushing. New commits show up in the pull request automatically,
but the reviewers are notified only when you comment.

Pull requests must be cleanly rebased on top of master without multiple branches
mixed into the PR.

**Git tip**: If your PR no longer merges cleanly, use `rebase master` in your
feature branch to update your pull request rather than `merge master`.

Before you make a pull request, squash your commits into logical units of work
using `git rebase -i` and `git push -f`. A logical unit of work is a consistent
set of patches that should be reviewed together: for example, upgrading the
version of a vendored dependency and taking advantage of its now available new
feature constitute two separate units of work. Implementing a new function and
calling it in another file constitute a single logical unit of work. The very
high majority of submissions should have a single commit, so if in doubt: squash
down to one.

After every commit, make sure the test suite passes. Include documentation
changes in the same pull request so that a revert would remove all traces of
the feature or fix.

### Commit messages

We rely on [git-journal][git-journal] to manage the list of changes in the file
`CHANGELOG.md`. To make this work, please adhere to a few simple rules.

This example commit message show all keywords and convetions to be used.

Apart from the summary line, the remaining content is optional and should be
used when needed. We rely on your sanity.

```txt
#1234 [Added] the fancy thing everyone looks for            | Summary line
                                                            |
Now I describe what I did in a detailed way.                | Body
This detail message will be handeled as a certain           | - Paragraph
paragraph. There is no need for a tag or a category.        |
                                                            |
- [Fixed] some very bas thing                               | - List
- [Added] detailed documentation about that thing :doc:     |
- [Changed] A to look now as B :internal:                   |
                                                            |
Reviewed-by: John Doe                                       | Footer
```

### Merge approval

WowStack maintainers use LGTM (Looks Good To Me) in comments on the code review
to indicate acceptance.

A change requires LGTMs from an absolute majority of the maintainers of each
component affected.

For more details, see the [MAINTAINERS](MAINTAINERS.toml) file.

### Sign your work

The sign-off is a simple line at the end of the explanation for the patch. Your
signature certifies that you wrote the patch or otherwise have the right to pass
it on.

Then you just add a line to every git commit message:

    Signed-off-by: Joe Smith <joe.smith@email.com>

Use your real name (sorry, no pseudonyms or anonymous contributions.)

If you set your `user.name` and `user.email` git configs, you can sign your
commit automatically with `git commit -s`.

### Becoming a maintainer

The procedures for adding new maintainers are explained in the global
`MAINTAINERS.toml` file in the repository.

Don't forget: being a maintainer is a time investment. Make sure you will have
time to make yourself available. You don't have to be a maintainer to make a
difference on the project!

[wowstack]: https://wowstack.io/ "WowStack"
[project-issues]: https://github.com/wowstack/classic-server/issues
[security-issues]: mailto:security@wowstack.io
[git-journal]: https://github.com/saschagrunert/git-journal
