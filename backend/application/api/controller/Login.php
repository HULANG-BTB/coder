<?php
/**
 * FileName: Login.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 9:53
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */


namespace app\api\controller;


use app\common\controller\Base;
use app\api\model\User as UserModel;
use think\App;
use think\captcha\Captcha;
use think\facade\Validate;
use think\facade\Session;

/**
 * Class Login
 * Author: Hu Lang
 * DateTime: 2019/9/27 9:54
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * @package app\api\controller
 * Description:
 */
class Login extends Base
{
    /**
     * Login constructor.
     * @param App|null $app
     */
    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new UserModel();
    }

    /**
     * Notes: 登录验证方法
     * DateTime: 2019/9/27 11:16
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return \think\response\Json
     * @throws \think\db\exception\DataNotFoundException
     * @throws \think\db\exception\ModelNotFoundException
     * @throws \think\exception\DbException
     */
    public function login () {
        $ret = [
            'code' => 0
        ];
        $username = $this->request->post('username/s', '');
        $password = $this->request->post('password/s', '');

        /**
         * 验证表单数据
         */
        $rule = [
            'username|用户名' => 'require|min:5|max:20',
            'password|密码' => 'require|min:6|max:20',
            'captcha|验证码' => 'require|captcha'
        ];
        $validate = Validate::make($rule);
        if (!$validate->check($this->request->post())) {
            $ret['msg'] = $validate->getError();
            return json($ret);
        }

        /**
         * 读取数据库用户
         */
        $user = $this->Model
            ->field(['uid','username', 'password'])
            ->where(['username' => $username])
            ->find();
        if (!$user) {
            $ret['msg'] = '用户不存在！';
            return json($ret);
        }

        /**
         * 验证用户密码
         */
        if (!$this->checkPassword($password, $user['password'])) {
            $ret['msg'] = '用户名或密码错误！';
            return json($ret);
        }

        /**
         * 登录成功
         */
        $user->loinIp = get_client_ipaddress();
        $user->save();
        Session::set('uid', $user->uid);
        $ret['code'] = 1;
        return json($ret);
    }

    /**
     * Notes: 登录退出方法
     * DateTime: 2019/9/27 12:45
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return \think\response\Json
     */
    public function logout () {
        Session::clear();
        $ret = [
            'code' => 1,
            'data' => null,
        ];
        return json($ret);
    }

    /**
     * Notes: 注册用户
     * DateTime: 2019/9/27 11:03
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return \think\response\Json
     */
    public function register () {

        $ret = [
            'code' => 0
        ];

        /**
         * 数据验证
         */
        $rule = [
            'username|用户名' => 'require|min:5|max:20',
            'password|密码' => 'require|min:6|max:20',
            'email|邮箱' => 'require|email',
            'school|学校' => 'max:25',
            'captcha|验证码' => 'require|captcha'
        ];
        $validate = Validate::make($rule);
        if (!$validate->check($this->request->post())) {
            $ret['msg'] = $validate->getError();
            return json($ret);
        }

        /**
         * 读取post数据
         */
        $username = $this->request->post('username', '');
        $password = $this->request->post('password', '');

        /**
         * 读取数据库数据
         */
        $user = $this->Model
            ->where(['username' => $username])
            ->count();
        $identify = \app\api\model\Option::get('identify');

        /**
         * 用户是否存在
         */
        if ($user) {
            $ret['msg'] = '用户已经存在！';
            return json($ret);
        }

        /**
         * 准备注册信息
         */
        $user = $this->request->post();
        $user['password'] = $this->encryptPassword($password);
        $user['identify'] = $identify;
        $user['create_ip'] = $user['login_ip'] = get_client_ipaddress();
        $result = $this->Model->save($user);
        if ($result) {
            $ret['msg'] = '注册成功！';
            Session::set('uid', $user->uid);
            $ret['code'] = 1;
            return json($ret);
        } else {
            $ret['msg'] = '注册失败，请稍后再试！';
            return json($ret);
        }

    }

    /**
     * Notes: 获取验证码
     * DateTime: 2019/9/27 10:04
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @return Captcha
     */
    public function captchaCode () {
        $captcha = new Captcha();
        $captcha->useCurve = false;
        $captcha->useNoise = false;
        $captcha->length = 4;
        return $captcha->entry();
    }

    /**
     * Notes: 检查密码是否匹配
     * DateTime: 2019/9/27 10:27
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @param $nPwd
     * @param $oPwd
     * @return bool
     */
    protected function checkPassword($nPwd, $oPwd) {
        $salt = substr(base64_decode($oPwd), 20);
        $enrpyptOld = base64_encode(sha1($nPwd, true).$salt);
        return $oPwd === $enrpyptOld;
    }

    /**
     * Notes: 获取加密字符串密码
     * DateTime: 2019/9/27 10:35
     * Author: Hu Lang
     * Email: admin@oibit.cn
     * @param $pwd
     * @return string
     */
    protected function encryptPassword($pwd) {
        $salt = substr(md5(time()),0,4);
        $encryptStr = base64_encode(sha1($pwd, true).$salt);
        return $encryptStr;
    }

}
